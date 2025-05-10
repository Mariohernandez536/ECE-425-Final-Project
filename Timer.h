/**
 * @file Timer.h
 *
 * @brief Interface for configuring Timer0A to generate a 1 Hz interrupt.
 *
 * This module sets up Timer0A in 32-bit periodic mode to trigger
 * once per second using a 50 MHz system clock. It is used to drive
 * time updates for the digital clock.
 */


/**
 * @brief Initializes Timer0A to trigger an interrupt every 1 second.
 *
 * - Assumes a 50 MHz system clock.
 * - Configures Timer0A in 32-bit periodic mode.
 * - Enables the timer and its interrupt in the NVIC.
 * - The Timer0A ISR (`TIMER0A_Handler`) should call `Clock_Tick()`.
 */
void Timer0A_Init_1Hz(void);

/**
 * @brief Timer0A interrupt handler.
 *
 * This ISR should clear the interrupt flag and call `Clock_Tick()`
 * to update the clock every second.
 */
void Timer0A_Handler(void);
