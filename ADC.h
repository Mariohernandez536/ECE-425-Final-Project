/**
 * @file ADC.h
 *
 * @brief Header file for the ADC driver.
 *
 * This file contains the function definitions for the ADC driver.
 *
 * ADC Module 0 is used to sample the potentiometer and the analog
 * light sensor that are connected on the EduBase board. ADC Module 0
 * is configured to sample the potentiometer first and the light sensor after.
 *
 * After the light sensor is sampled, an interrupt signal is set to 
 * indicate that the sampling sequence has ended. After the conversion
 * results have been read from the corresponding FIFO, the interrupt is cleared.
 *
 * The following pins are used:
 *  - Potentiometer   <-->  Tiva LaunchPad Pin PE2 (Channel 1)
 *  - Light Sensor    <-->  Tiva LaunchPad Pin PE1 (Channel 2)
 *
 * @author Mario Hernandez
 *
 */

#include "TM4C123GH6PM.h"
#include "SysTick_Delay.h"

/**
 * @brief Initializes ADC0 and configures it to sample from PE1 (AIN2).
 *
 * Sets up GPIO Port E, enables analog input on PE1,
 * and configures Sample Sequencer 0 for single software-triggered sampling.
 */
void ADC_Init(void);

/**
 * @brief Samples the analog voltage from PE1 and stores it in a buffer.
 *
 * Initiates a conversion, waits for completion, and stores the result
 * as a voltage (0.0 to .6 V) in the specified index of the provided buffer.
 *
 * @param analog_value_buffer Pointer to a double array; result is stored at index 1.
 */
void ADC_Sample(double analog_value_buffer[]);

/**
 * @brief Converts a floating-point voltage to an 8-bit digital value (0–255).
 *
 * @param voltage Voltage value between 0.0 and .6
 * @return Integer between 0 and 255 representing the scaled digital value
 */
int Analog_Voltage_to_Digital(double voltage);
