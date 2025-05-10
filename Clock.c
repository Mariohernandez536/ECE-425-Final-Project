/**
 * @file Clock.c
 * @brief Handles timekeeping and alarm control logic for the Digital Clock.
 *
 * This module manages the internal time (HH:MM:SS), allows manual time setting,
 * and compares the current time to a user-set alarm. When the time matches,
 * the alarm is activated for 5 seconds via LEDs and buzzer.
 */

#include "Clock.h"
#include "GPIO.h"
#include "Alarm.h"
#include "EduBase_LCD.h"
#include <stdio.h>

// ==============================
// Timekeeping Variables
// ==============================
static int hour = 0;
static int minute = 0;
static int second = 0;

// ==============================
// Alarm Time Variables (shared with main)
// ==============================
int alarm_hour = 0;
int alarm_minute = 0;
int alarm_second = 0;

// ==============================
// Internal State
// ==============================
static int alarm_enabled = 1;
static int alarm_active_counter = 0;  // Tracks how long alarm stays on
volatile int update_display_flag = 0; // Signals main to update LCD

// ==============================
// Initialization
// ==============================
void Clock_Init(void)
{
    hour = 0;
    minute = 0;
    second = 0;
    update_display_flag = 1; // Force display on startup
}

// ==============================
// Manual Time Setting Function
// ==============================
void Clock_Set_Time(int h, int m, int s)
{
    hour = h % 24;
    minute = m % 60;
    second = s % 60;
    update_display_flag = 1; // Trigger LCD update
}

// ==============================
// Timekeeping Tick Function
// ==============================
void Clock_Tick(void)
{
    second++;
    if (second >= 60)
    {
        second = 0;
        minute++;
    }
    if (minute >= 60)
    {
        minute = 0;
        hour++;
    }
    if (hour >= 24)
    {
        hour = 0;
    }

    Clock_Check_Alarm();           // Check if alarm should go off
    update_display_flag = 1;       // Notify main to update LCD
}

// ==============================
// Alarm Check and Timer Control
// ==============================
void Clock_Check_Alarm(void)
{
    if (alarm_enabled &&
        hour == alarm_hour &&
        minute == alarm_minute &&
        second == alarm_second)
    {
        alarm_active_counter = 5;         // Alarm stays on for 5 seconds
        EduBase_LEDs_Output(0x0F);        // Turn on all LEDs
        Alarm_On();                       // onboard LED
    }

    if (alarm_active_counter > 0)
    {
        alarm_active_counter--;

        if (alarm_active_counter == 0)
        {
            Alarm_Off();
            EduBase_LEDs_Output(0x00);
        }
    }
}

// ==============================
// Clock Getters
// ==============================
int Clock_Get_Hour(void)   { return hour; }
int Clock_Get_Minute(void) { return minute; }
int Clock_Get_Second(void) { return second; }

// ==============================
// Alarm Time Setters
// ==============================
void Alarm_Add_Hour(void)
{
    alarm_hour = (alarm_hour + 1) % 24;
}

void Alarm_Add_Minute(void)
{
    alarm_minute = (alarm_minute + 1) % 60;
}

void Alarm_Add_Second(void)
{
    alarm_second = (alarm_second + 1) % 60;
}

// ==============================
// Alarm Enable/Disable Toggle
// ==============================
void Clock_Toggle_Alarm(void)
{
    alarm_enabled ^= 1; // Flip between 0 (OFF) and 1 (ON)
}

int Clock_Alarm_Is_Enabled(void)
{
    return alarm_enabled;
}
