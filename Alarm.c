// Alarm.c
#include "TM4C123GH6PM.h"
#include "Alarm.h"

// Initialize the alarm by setting up the buzzer on PB6 and an LED on PF1.
void Alarm_Init(void) {
    SYSCTL->RCGCGPIO |= 0x22;
    while ((SYSCTL->PRGPIO & 0x22) != 0x22) {}

    GPIOB->DIR |= (1 << 6);
    GPIOB->DEN |= (1 << 6);

    GPIOF->DIR |= (1 << 1);
    GPIOF->DEN |= (1 << 1);

    GPIOB->DATA &= ~(1 << 6);
    GPIOF->DATA &= ~(1 << 1);
}

void Alarm_On(void)
{
    SYSCTL->RCGCGPIO |= (1 << 1) | (1 << 5);
    while ((SYSCTL->PRGPIO & ((1 << 1) | (1 << 5))) == 0);

    GPIOB->DIR |= (1 << 6);
    GPIOB->DEN |= (1 << 6);

    GPIOF->DIR |= (1 << 1);
    GPIOF->DEN |= (1 << 1);

    GPIOB->DATA |= (1 << 6);
    GPIOF->DATA |= (1 << 1);
}

void Alarm_Off(void) {
    GPIOB->DATA &= ~(1 << 6);
    GPIOF->DATA &= ~(1 << 1);
}

void Alarm_Toggle(void) {
    GPIOB->DATA ^= (1 << 6);
    GPIOF->DATA ^= (1 << 1);
}
