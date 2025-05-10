#include "ADC.h"
#include "TM4C123GH6PM.h"

/**
 * @brief Initializes ADC0 for sampling only the light sensor (PE1).
 *
 * This temporary setup is used for debugging the light sensor.
 */
void ADC_Init(void)
{
	// Enable clock for ADC0 module
	SYSCTL->RCGCADC |= 0x01;      // Enable ADC0 clock
	SysTick_Delay1ms(1);          // 1 ms delay after enabling clock

	// Enable clock for GPIO Port E (for PE1)
	SYSCTL->RCGCGPIO |= 0x10;     // Set bit 4 to enable Port E clock

	// Wait for Port E to be ready
	while ((SYSCTL->PRGPIO & 0x10) == 0); // Wait for Port E ready

	// Set PE1 as input
	GPIOE->DIR &= ~0x02;         // PE1 as input

	// Disable digital function on PE1
	GPIOE->DEN &= ~0x02;         // Disable digital function on PE1

	// Enable analog mode on PE1
	GPIOE->AMSEL |= 0x02;        // Enable analog mode on PE1

	// Enable alternate function for PE1
	GPIOE->AFSEL |= 0x02;        // Set bit 1 for alternate function

	// Disable Sample Sequencer 0 during configuration
	ADC0->ACTSS &= ~0x01;        // Disable SS0 during config

	// Configure SS0 for software trigger
	ADC0->EMUX &= ~0x000F;       // Set bits 3:0 for software trigger on SS0

	// Set the sequence: Only sample channel 2 (PE1)
	ADC0->SSMUX0 = 0x00000002;   // First = AIN2 (PE1)

	// Configure SSCTL0: Interrupt enable (IE0), End of sequence (END0)
	ADC0->SSCTL0 = 0x00000006;   // Bit 1 (IE0) and Bit 2 (END0) set

	// Re-enable Sample Sequencer 0
	ADC0->ACTSS |= 0x01;         // Enable SS0
}

/**
 * @brief Starts the ADC conversion and reads result from PE1 (light sensor).
 *
 * @param analog_value_buffer Array to store the sampled value
 */
void ADC_Sample(double analog_value_buffer[])
{
	// Start sampling using SS0
	ADC0->PSSI = 0x01; // Set bit 0 to initiate SS0

	// Wait for conversion to complete
	while ((ADC0->RIS & 0x01) == 0); // Wait until RIS0 is set

	// Read result from FIFO (PE1 only)
	unsigned int result_pe1 = ADC0->SSFIFO0 & 0x0FFF; // PE1 - Light Sensor

	// Convert to voltage and store in buffer
	analog_value_buffer[1] = (result_pe1 * 3.3) / 4095.0; // PE1 - Light Sensor

	// Clear interrupt flag
	ADC0->ISC = 0x01; // Clear SS0 interrupt by writing 1 to bit 0
}
int Analog_Voltage_to_Digital(double voltage)
{
    if (voltage <= 0.0)
        return 0;
    else if (voltage >= 3.3)
        return 255;
    else
        return (int)((voltage / 3.3) * 255);
}
