/**
 * @file main.c
 *
 * @brief Digital Clock with Alarm and Light Sensor Snooze – EduBase Board
 *
 * This program implements a digital clock with manual time setting,
 * alarm functionality, snooze cycling, and light sensor-based dismissal.
 * The time is displayed on a LCD, and user interaction is handled
 * through buttons SW2–SW5 on the EduBase board.
 *
 * Features:
 *  - Manual time set mode on startup using buttons
 *  - Alarm set and enable/disable control
 *  - Alarm triggers LEDs and snooze cycle
 *  - Light sensor (PE1) used to turn off the alarm
 *  - LCD display shows current time and status
 *
 * Pin Assignments:
 *  - LCD Data (D4–D7)     : PA2–PA5
 *  - LCD Enable (E)       : PC6
 *  - LCD RS (Register Select): PE0
 *  - EduBase LEDs (LED0–3): PB0–PB3
 *  - Alarm LED Indicator  : PF1 - first iteration
 *  - Buttons SW2–SW5      : PD3 (SW2), PD2 (SW3), PD1 (SW4), PD0 (SW5)
 *  - Light Sensor Input   : PE1 (AIN2)
 *
 * Modules Used:
 *  - Clock        : Handles timekeeping and alarm time
 *  - Display      : Updates LCD with current time
 *  - Timer        : Generates 1 Hz interrupt using Timer0A
 *  - SysTick_Delay: Provides ms/us blocking delays
 *  - Alarm        : Controls buzzer and alarm LED
 *  - GPIO         : Initializes LEDs and buttons
 *  - Buttons      : Interrupt-driven input from SW2–SW5
 *  - ADC          : Samples light sensor on PE1 to cancel alarm
 *
 * Author: [Mario Hernandez]
 */
#include "Clock.h"
#include "Display.h"
#include "Timer.h"
#include "SysTick_Delay.h"
#include "Alarm.h"
#include "GPIO.h"
#include "EduBase_LCD.h"
#include "Buttons.h"
#include "ADC.h"
#include <stdio.h>

// Tracks time until message clears and clock resumes
static int lcd_message_timer = 0;

// Time set flag
int time_set_mode = 1;

// Temporary time variables during setup
int temp_hour = 0;
int temp_minute = 0;
int temp_second = 0; // Not used

// Light sensor buffer
static double adc_buffer[8];
int alarm_triggered_flag = 0;

// Snooze logic
int snooze_mode = 0;
int led_flash_timer = 0;
int snooze_countdown = 5;

// External Clock.c variables
extern volatile int update_display_flag;
extern int alarm_hour;
extern int alarm_minute;
extern int alarm_second;

int main(void)
{
    SysTick_Delay_Init();
    SysTick_Delay1ms(100);

    Display_Init();
    Clock_Init();
    Alarm_Init();
    Buttons_Init();
    EduBase_LEDs_Init();
    ADC_Init();
    Timer0A_Init_1Hz(); // 1Hz tick

    while (1)
    {
        // -------- TIME SET MODE --------
        if (time_set_mode)
        {
            EduBase_LCD_Set_Cursor(0, 0);
            EduBase_LCD_Display_String("Set Time Mode   ");

            EduBase_LCD_Set_Cursor(0, 1);
            char buf[17];
            sprintf(buf, "SET %02d:%02d", temp_hour, temp_minute);
            EduBase_LCD_Display_String(buf);

            if (Button_HasEvent())
            {
                ButtonEvent e = Button_GetEvent();
                switch (e)
                {
                    case BUTTON_SW2_PRESSED:
                        temp_hour = (temp_hour + 1) % 24;
                        break;
                    case BUTTON_SW3_PRESSED:
                        temp_minute = (temp_minute + 1) % 60;
                        break;
                    case BUTTON_SW4_PRESSED:
                        Clock_Set_Time(temp_hour, temp_minute, 0);
                        time_set_mode = 0;
                        EduBase_LCD_Set_Cursor(0, 0);
                        EduBase_LCD_Display_String("Digital Clock   ");
                        break;
                    default:
                        break;
                }

                SysTick_Delay1ms(250);
            }
        }

        // -------- NORMAL CLOCK MODE --------
        else
        {
            if (update_display_flag)
            {
                update_display_flag = 0;

                if (lcd_message_timer > 0)
                {
                    lcd_message_timer--;
                }
                else
                {
                    Display_UpdateTime(
                        Clock_Get_Hour(),
                        Clock_Get_Minute(),
                        Clock_Get_Second()
                    );
                }

                if (snooze_mode)
                {
                    if (led_flash_timer > 0)
                    {
                        led_flash_timer--;
                        if (led_flash_timer == 0)
                        {
                            EduBase_LEDs_Output(0x00); // Turn LEDs OFF
                            snooze_countdown = 5;      // Start countdown
                        }
                    }
                    else
                    {
                        snooze_countdown--;
                        char cd_buf[8];
                        sprintf(cd_buf, "CD:%02d", snooze_countdown);
                        EduBase_LCD_Set_Cursor(11, 1);
                        EduBase_LCD_Display_String(cd_buf);

                        if (snooze_countdown <= 0)
                        {
                            EduBase_LEDs_Output(0x0F); // Flash LEDs
                            led_flash_timer = 5;       // ON for 5s
                        }
                    }
                }
            }

            // Alarm triggers once
            if (Clock_Alarm_Is_Enabled() &&
                Clock_Get_Hour() == alarm_hour &&
                Clock_Get_Minute() == alarm_minute &&
                Clock_Get_Second() == alarm_second &&
                !alarm_triggered_flag)
            {
                alarm_triggered_flag = 1;
                snooze_mode = 1;

                EduBase_LEDs_Output(0x0F); // LEDs ON
                led_flash_timer = 5;       // Stay on 5s

                EduBase_LCD_Set_Cursor(0, 1);
                EduBase_LCD_Display_String("** ALARM ACTIVE **");
            }

            // Alarm setup buttons
            if (Button_HasEvent())
            {
                ButtonEvent event = Button_GetEvent();
                switch (event)
                {
                    case BUTTON_SW2_PRESSED:
                        alarm_hour = (alarm_hour + 1) % 24;
                        EduBase_LCD_Set_Cursor(0, 1);
                        EduBase_LCD_Display_String("                ");
                        EduBase_LCD_Set_Cursor(0, 1);
                        char buf2[17];
                        sprintf(buf2, "ALARM %02d:%02d", alarm_hour, alarm_minute);
                        EduBase_LCD_Display_String(buf2);
                        lcd_message_timer = 2;
                        break;

                    case BUTTON_SW3_PRESSED:
                        Alarm_Add_Minute();
                        EduBase_LCD_Set_Cursor(0, 1);
                        EduBase_LCD_Display_String("                ");
                        EduBase_LCD_Set_Cursor(0, 1);
                        char buf3[17];
                        sprintf(buf3, "ALARM %02d:%02d", alarm_hour, alarm_minute);
                        EduBase_LCD_Display_String(buf3);
                        lcd_message_timer = 2;
                        break;

                    case BUTTON_SW4_PRESSED:
                        Clock_Toggle_Alarm();
                        EduBase_LCD_Set_Cursor(0, 1);
                        EduBase_LCD_Display_String("                ");
                        EduBase_LCD_Set_Cursor(0, 1);
                        EduBase_LCD_Display_String(
                            Clock_Alarm_Is_Enabled() ? "Alarm ON" : "Alarm OFF"
                        );
                        lcd_message_timer = 2;
                        break;

                    default:
                        break;
                }
            }

            // Light sensor dismiss (cover sensor)
            if (Clock_Alarm_Is_Enabled() && alarm_triggered_flag)
            {
                ADC_Sample(adc_buffer);

                if (adc_buffer[1] < 0.06)
                {
                    Alarm_Off();
                    EduBase_LEDs_Output(0x00);
                    EduBase_LCD_Set_Cursor(0, 1);
                    EduBase_LCD_Display_String("Turned OFF");
                    lcd_message_timer = 2;

                    // Reset all alarm flags
                    alarm_triggered_flag = 0;
                    snooze_mode = 0;
                    led_flash_timer = 0;
                    snooze_countdown = 5;

                    // Clear countdown area
                    EduBase_LCD_Set_Cursor(11, 1);
                    EduBase_LCD_Display_String("     ");
                }
            }
        }
    }
}
