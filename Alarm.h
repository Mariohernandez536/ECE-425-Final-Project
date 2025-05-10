/**
 * @file Alarm.h
 *
 * @brief Interface for alarm output control using GPIO.
 *
 * This module controls the alarm indicators: a additional LED (PF1).
 * It provides functions to initialize, activate, deactivate, or toggle these outputs.
 -------------Some of these functions include the possible additon of a buzzer in the future so they have a buzzer included. 
 */

/**
 * @brief Initializes the GPIO pins used for alarm output.
 *
 * Configures PF1 (LED) as digital outputs and sets them LOW.
 */
void Alarm_Init(void);

/**
 * @brief Turns the alarm ON.
 *
 * Sets PF1 HIGH to activate buzzer and LED.
 */
void Alarm_On(void);

/**
 * @brief Turns the alarm OFF.
 *
 * Sets PF1 LOW to LED.
 */
void Alarm_Off(void);

/**
 * @brief Toggles the current state of the alarm output pins.
 *
 * Inverts the output PF1.
 */
void Alarm_Toggle(void);
