#include "LPC17xx.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_gpdma.h"
#include "lpc17xx_timer.h"

// Definitions
#define DAC_UPDATE_INTERVAL 521 // DAC time out value for a DAC Update Rate of 48 kHz and PCLK = 25 MHz
#define DMA_SIZE 0  // Transfer size: x samples
#define NUM_SAMPLES  0  // Total number of samples for the full sine wave fo the Transfer size
#define DMA_ADC_BUFFER_SIZE 0  // Buffer size for ADC - DMA transfer
#define T0_PRESCALE_VALUE 100   // Timer0 Prescaler value for 100 MHz clock -> 1 µs resolution
#define T0_MATCH_VALUE 0   // Timer0 match value for 

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
 * @brief Configure Timer0 and its match0 register. Match0 will be used to generate interrupts.
 * 
 */
void configure_timer_and_match(void);

/**
 * @brief Start Timer0 in timer mode.
 * 
 */
void start_timer(void);

/**
 * @brief Handle the Match 0 interrupt for Timer0. This function will start an ADC conversion.
 * 
 */
void TIMER0_IRQHandler(void);