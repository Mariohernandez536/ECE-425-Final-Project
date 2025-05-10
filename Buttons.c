#include "TM4C123GH6PM.h"
#include "Buttons.h"
#include "SysTick_Delay.h"

// Internal state to track most recent button press
static volatile ButtonEvent current_event = BUTTON_NONE;

void Buttons_Init(void)
{
    SYSCTL->RCGCGPIO |= 0x08;           // Enable Port D clock
    while ((SYSCTL->PRGPIO & 0x08) == 0);

    // Unlock PD3 for use (SW5)
    GPIOD->LOCK = 0x4C4F434B;           // Unlock PD3
    GPIOD->CR   |= (1 << 3);            // Allow changes to PD3

    GPIOD->DIR  &= ~0x0F;               // PD0–PD3 as input
    GPIOD->DEN  |= 0x0F;                // Digital enable
    GPIOD->IS   &= ~0x0F;               // Edge-sensitive
    GPIOD->IEV  |= 0x0F;                // Rising edge
    GPIOD->ICR   = 0x0F;                // Clear interrupts
    GPIOD->IM   |= 0x0F;                // Enable interrupt

    NVIC_EnableIRQ(GPIOD_IRQn);
}

void GPIOD_Handler(void)
{
    if (GPIOD->RIS & (1 << 3)) {
        GPIOD->ICR = (1 << 3);
        current_event = BUTTON_SW2_PRESSED; // PD3 = physical SW2
				SysTick_Delay1ms(35); // debounce delay
    }
    else if (GPIOD->RIS & (1 << 2)) {
        GPIOD->ICR = (1 << 2);
        current_event = BUTTON_SW3_PRESSED; // PD2 = physical SW3
			SysTick_Delay1ms(35); // debounce delay
    }
    else if (GPIOD->RIS & (1 << 1)) {
        GPIOD->ICR = (1 << 1);
        current_event = BUTTON_SW4_PRESSED; // PD1 = physical SW4
				SysTick_Delay1ms(25); // debounce delay
    }
    else if (GPIOD->RIS & (1 << 0)) {
        GPIOD->ICR = (1 << 0);
        current_event = BUTTON_SW5_PRESSED; // PD0 = physical SW5
				SysTick_Delay1ms(30); // debounce delay			(unused)
    }
}



bool Button_HasEvent(void)
{
    return current_event != BUTTON_NONE;
}

ButtonEvent Button_GetEvent(void)
{
    ButtonEvent temp = current_event;
    current_event = BUTTON_NONE;
    return temp;
}
