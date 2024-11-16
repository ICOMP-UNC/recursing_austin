#ifndef SYSTEM_LOGIC_H
#define SYSTEM_LOGIC_H

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_gpdma.h"
#include "lpc17xx_exti.h"

// Boolean values definitions
#define TRUE 1
#define FALSE 0

// GPIO directions definitions
#define INPUT 0
#define OUTPUT 1

// Set - Clear definitions
#define SET 1
#define CLEAR 0

#define DAC_UPDATE_INTERVAL 521 // DAC time out value for a DAC Update Rate of 48 kHz and PCLK = 25 MHz

#define NUM_SAMPLES  0  // Total number of samples for the full sine wave for the Transfer size

#define T0_PRESCALE_VALUE 100   // Timer0 Prescaler value for 100 MHz clock -> 1 µs resolution

// ADC Sampling rate = 44100 Hz
// ADC Clock Frequency = Sampling rate x Number of clocks per conversion 
// 44100 x 65 = 2866500 Hz
// Time for one conversion = Number of clocks per conversion x Time per clock cycle
// 65 x 1/2866500 = 22.67 µs
// MatchValue = desired time (seconds) / tick duration (seconds) = 22.67 µs / 1 µs = 22.67
#define T0_MATCH_VALUE (uint32_t)(23)   // Timer0 match value for start a ad conversion every 22.67 µs aproximately

#define ADC_FREQ 44100 // ADC conversion rate, 44.1 kHz for sound quality

// Buffer size for ADC - DMA transfer. Buffer Size = (Sampling rate) x (duration) = 44100 x 0.01 = 441 samples
#define SIZE_BUFFER_ADC (uint16_t)(400) // Buffer size for ADC samples

#define DMA_ADC_CHANNEL (uint8_t)(0) // DMA channel for ADC: O, highest priority
#define DMA_DAC_CHANNEL (uint8_t)(1) // DMA channel for DAC: 1, lower priority

// Variables Definitions

/**
 * @brief Struct with bitfield to store status flags
 * 
 */
typedef struct 
{
    uint8_t tuning_mode : 1; // 1 bit flag to indicate the mode of operation
    uint8_t buffer_adc_full : 1; // 1 bit flag to indicate that the ADC buffer is full
}StatusFlags;

uint16_t adc_buffer[SIZE_BUFFER_ADC] = {0}; // Circular Buffer to store the ADC results
uint16_t buffer_index = 0; // Index to store the ADC results in the buffer

// Function Prototypes

/**
 * @brief Configure the DAC peripheral. Enable DAC - DMA mode and double buffering. 
 * The DAC update rate is set to 48 kHz.   
 * 
 */
void configure_dac(void);

/**
 * @brief Configure GPDMA for transferring data from memory to DAC. 
 * @param table Pointer to the waveform table
 */
void configure_dma(uint32_t* table_waveform);

/**
 * @brief Configure Timer0 and its match0 register. Match0 will be used to generate interrupts
 * for ADC conversions.
 */
void configure_timer_and_match(void);

/**
 * @brief Configure the External Interrupt for the switch connected to P2.10.
 * Allows to change modes of operation, from the instrument mode to the tuning mode.
 */
void configure_external_interrupt(void);

/**
 * @brief Configure ADC. Enable Channel 5 and interrupts. Enable ADC - DMA transmission
 * 
 */
void configure_adc(void);

/**
 * @brief Start Timer0 in timer mode.
 * 
 */
void start_timer(void);

/**
 * @brief Start an ADC conversion.
 * 
 */
void start_adc_conversion(void);

/**
 * @brief Handle the Match 0 interrupt for Timer0. This function will start an ADC conversion.
 * 
 */
void TIMER0_IRQHandler(void);

/**
 * @brief Overwrite the interrupt handle routine for (EINT0)
 * Allows to change modes of operation, from the instrument mode to the tuning mode.
 */
void EINT0_IRQHandler(void);    

/**
 * @brief Handle the ADC interrupt. Save the conversion result in the ADC circular buffer.
 * Update the buffer index to store the latest value.
 */
void ADC_IRQHandler(void);

/**
 * @brief Handle the DMA interrupt. Check the status of the DMA channel 0 and clear the interrupt flag.
 * Change the buffer status if full and call the sound frequency analysis function.
 */
void DMA_IRQHandler(void);

#endif
