/**
 * @file Clock.h
 *
 * @brief Interface for timekeeping and alarm control logic.
 *
 * This module manages the digital clock's current time (HH:MM:SS),
 * allows setting the time manually, and handles checking and triggering the alarm.
 * The clock updates once per second via a timer interrupt.
 */
#ifndef CLOCK_H
#define CLOCK_H

// External variables shared with main
extern volatile int update_display_flag;
extern int alarm_hour;
extern int alarm_minute;
extern int alarm_second;

// Clock setup and control------------------------

/**
 * @brief Initializes the clock module.
 *
 * Resets the internal time to 00:00:00 and sets update flag.
 */
void Clock_Init(void);

/**
 * @brief Updates the clock time by 1 second.
 *
 * Increments the internal time variables and wraps as needed.
 * Also checks if the current time matches the alarm.
 */
void Clock_Tick(void);

/**
 * @brief Checks if the current time matches the alarm time.
 *
 * If the alarm is enabled and the time matches, activates alarm for 5 seconds.
 * Handles countdown of how long the alarm stays active.
 */
void Clock_Check_Alarm(void);

/**
 * @brief Sets the current time manually.
 *
 * @param h Hour value (0–23)
 * @param m Minute value (0–59)
 * @param s Second value (0–59)
 */
void Clock_Set_Time(int h, int m, int s);

// Get current time values--------------------------

/**
 * @brief Returns the current hour (0–23).
 */
int Clock_Get_Hour(void);

/**
 * @brief Returns the current minute (0–59).
 */
int Clock_Get_Minute(void);

/**
 * @brief Returns the current second (0–59).
 */
int Clock_Get_Second(void);

// Alarm setters---------------------------------------
/**
 * @brief Adds 1 hour to the alarm time (wraps at 24).
 */
void Alarm_Add_Hour(void);

/**
 * @brief Adds 1 minute to the alarm time (wraps at 60).
 */
void Alarm_Add_Minute(void);

/**
 * @brief Adds 1 second to the alarm time (wraps at 60).
 */
void Alarm_Add_Second(void);

// Alarm control------------------------------------------------
/**
 * @brief Toggles whether the alarm is enabled or disabled.
 */
void Clock_Toggle_Alarm(void);

/**
 * @brief Returns whether the alarm is currently enabled.
 *
 * @return 1 if enabled, 0 if disabled
 */

int Clock_Alarm_Is_Enabled(void);

#endif
