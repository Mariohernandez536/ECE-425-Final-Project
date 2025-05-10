/**
 * @file Display.c
 * @brief Displays time in HH:MM:SS on EduBase LCD
 */

#include "Display.h"
#include "EduBase_LCD.h"
#include <stdio.h>

void Display_Init(void)
{
    EduBase_LCD_Init();
    EduBase_LCD_Clear_Display();
    
    // Set cursor to first row, first column
    EduBase_LCD_Set_Cursor(0, 0);
    EduBase_LCD_Display_String("Digital Clock");

    // Set cursor to second row, first column
    EduBase_LCD_Set_Cursor(0, 1);
    EduBase_LCD_Display_String("                "); // Clear second line
}

void Display_UpdateTime(int hour, int minute, int second)
{
    char str[17];
    sprintf(str, "%02d:%02d:%02d", hour, minute, second);

    EduBase_LCD_Set_Cursor(0, 1);
    EduBase_LCD_Display_String("                ");  // Full row clear
    EduBase_LCD_Set_Cursor(0, 1);
    EduBase_LCD_Display_String(str);
}
