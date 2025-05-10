/**
 * @file Timer.c
 * @brief Timer0A configuration for 1 Hz time interrupt.
 */

#include "TM4C123GH6PM.h"
#include "Clock.h"

void Timer0A_Init_1Hz(void)
{
    // Enable Timer0 clock
    SYSCTL->RCGCTIMER |= 0x01;

    // Disable Timer0A before configuration
    TIMER0->CTL = 0x00;

    // Configure for 32-bit timer mode
    TIMER0->CFG = 0x00;

    // Configure Timer0A for periodic mode
    TIMER0->TAMR = 0x02;

    // Set reload value for 1Hz (50 MHz clock assumed)
    TIMER0->TAILR = 50000000 - 1;

    // Clear timeout flag
    TIMER0->ICR = 0x01;

    // Enable Timer0A timeout interrupt
    TIMER0->IMR = 0x01;

    // Enable Timer0A interrupt in NVIC
    NVIC_EnableIRQ(TIMER0A_IRQn);

    // Enable Timer0A
    TIMER0->CTL |= 0x01;
}

void TIMER0A_Handler(void)
{
    TIMER0->ICR = 0x01;  // Clear interrupt flag
    Clock_Tick();        // Advance time and trigger update
}
