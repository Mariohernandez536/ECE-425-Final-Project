/**
 * @file Buttons.h
 *
 * @brief Interface for handling button inputs on the EduBase Board (SW2–SW5).
 *
 * This module configures GPIO Port D (PD0–PD3) as input buttons and uses
 * interrupts to detect button presses. It tracks button events with software
 * debouncing and allows polling the most recent press.
 */
#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdbool.h>

// Enum to represent button events
typedef enum {
    BUTTON_NONE,
    BUTTON_SW2_PRESSED,
    BUTTON_SW3_PRESSED,
    BUTTON_SW4_PRESSED,
    BUTTON_SW5_PRESSED
} ButtonEvent;


/**
 * @brief Initializes the GPIO for EduBase buttons (PD0–PD3) and enables interrupts.
 *
 * Unlocks PD3 as required, configures all pins as inputs with digital enable,
 * and sets up interrupt detection on rising edges.
 */
void Buttons_Init(void);

/**
 * @brief Returns whether any button press event has been registered.
 *
 * @return true if a button event is pending, false otherwise.
 */
bool Button_HasEvent(void);

/**
 * @brief Returns and clears the most recent button press event.
 *
 * After calling this, the stored event is reset to BUTTON_NONE.
 *
 * @return The last button press event (e.g., BUTTON_SW3_PRESSED).
 */
ButtonEvent Button_GetEvent(void);

#endif
