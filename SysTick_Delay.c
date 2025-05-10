#include "TM4C123GH6PM.h"

void SysTick_Delay_Init(void)
{
    SysTick->CTRL = 0;          // Disable SysTick
    SysTick->LOAD = 0x00FFFFFF;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x05;       // Enable SysTick with system clock
}

void SysTick_Delay1ms(uint32_t ms)
{
    while (ms--)
    {
        SysTick->LOAD = 16000 - 1; // 1 ms @ 16 MHz
        SysTick->VAL = 0;
        while ((SysTick->CTRL & 0x10000) == 0);
    }
}

void SysTick_Delay1us(uint32_t us)
{
    while (us--)
    {
        SysTick->LOAD = 16 - 1;  // 1 us @ 16 MHz
        SysTick->VAL = 0;
        while ((SysTick->CTRL & 0x10000) == 0);
    }
}
