/**
 * @file Display.h
 *
 * @brief Interface for LCD-based time display on the EduBase Board.
 *
 * This module handles initializing the LCD and updating the time display
 * in HH:MM:SS format on the second row of the screen.
 */


/**
 * @brief Initializes the EduBase LCD display.
 *
 * Clears the display, shows "Digital Clock" on the first row,
 * and clears the second row for time updates.
 */
void Display_Init(void);

/**
 * @brief Updates the time shown on the LCD.
 *
 * Displays the time in HH:MM:SS format at the beginning of the second row.
 *
 * @param hour   Current hour value (0–23)
 * @param minute Current minute value (0–59)
 * @param second Current second value (0–59)
 */
void Display_UpdateTime(int hour, int minute, int second);
