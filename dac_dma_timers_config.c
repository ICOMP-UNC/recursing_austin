#include "dac_dma_timers_config.h"

// Function Definitions

void configure_dac(void) 
{
    // use P0.26 as DAC output. Configure PINSEL for DAC output
    // dac registers configuration
    DAC_CONVERTER_CFG_Type DAC_ConfigStruct;    // DAC configuration structure variable
    
    DAC_ConfigStruct.CNT_ENA = SET;            // Enable DAC counter mode
    DAC_ConfigStruct.DMA_ENA = SET;            // Enable DAC-DMA mode
    DAC_ConfigStruct.DBLBUF_ENA = SET;         // Enable DAC double buffering for smoother output

    DAC_Init(LPC_DAC);  // Initialize DAC peripheral

    // Set the DAC time out value: For a DAC Update Rate of 48 kHz, and PCLK = 25 MHz, the time out 
    // value is DAC_UPDATE_INTERVAL = PCLK / (48 kHz) = 521
    DAC_SetDMATimeOut(LPC_DAC, DAC_UPDATE_INTERVAL);    

    // Set the DAC configuration
    DAC_ConfigDAConverterControl(LPC_DAC, &DAC_ConfigStruct);
}

void configure_dma(uint32_t* table_waveform)
{
    GPDMA_Channel_CFG_Type GPDMA_cfg;   // DMA configuration structure
    GPDMA_LLI_Type DMA_LLI_struct;      // DMA linked list item for continuous transfer 

    // Set up the DMA linked list for continuous waveform transfer
    DMA_LLI_struct.SrcAddr = (uint32_t)table_waveform;              // Source: DAC waveform table   
    DMA_LLI_struct.DstAddr = (uint32_t) & (LPC_DAC->DACR);          // Destination: DAC register
    DMA_LLI_struct.NextLLI = (uint32_t)&DMA_LLI_struct;             // Point to itself for continuous transfer
    DMA_LLI_struct.Control = (NUM_SAMPLES << 0) |                   // Transfer size
                            (2 << 18)   |                           // Source width: 32-bit
                            (2 << 21)   |                           // Destination width: 32-bit
                             (SET << 26) |                           // Source increment
                             (RESET << 27) |                         // Destination increment
                             (SET << 31);                            // Terminal count interrupt enable

    // Configure DMA channel0 for memory-to-peripheral transfer
    GPDMA_cfg.ChannelNum = 0;         // Use channel 0
    GPDMA_cfg.SrcMemAddr = (uint32_t)table_waveform; // Source: DAC waveform table
    GPDMA_cfg.DstMemAddr = 0;         // No memory destination (peripheral)
    GPDMA_cfg.TransferSize = NUM_SAMPLES; // Transfer size: x samples
    GPDMA_cfg.TransferWidth = 0;      // Not used
    GPDMA_cfg.TransferType = GPDMA_TRANSFERTYPE_M2P; // Memory to peripheral - DMA control
    GPDMA_cfg.SrcConn = 0;            // Source is memory
    GPDMA_cfg.DstConn = GPDMA_CONN_DAC; // Destination is DAC
    GPDMA_cfg.DMALLI = (uint32_t)&DMA_LLI_struct; // Linked list for continuous transfer

    // Configure DMA Channel1 for peripheral (ADC) to memory transfer
    GPDMA_cfg.ChannelNum = 1;         // Use channel 1
    GPDMA_cfg.SrcMemAddr = 0;         // No memory source (peripheral: ADC)
    GPDMA_cfg.DstMemAddr = (uint32_t)table_waveform; // Destination: DAC waveform table
    GPDMA_cfg.TransferSize = DMA_ADC_BUFFER_SIZE; // Transfer size:
    GPDMA_cfg.TransferWidth = 0;      // Not used
    GPDMA_cfg.TransferType = GPDMA_TRANSFERTYPE_P2M; // Peripheral to memory - DMA control
    GPDMA_cfg.SrcConn = GPDMA_CONN_ADC; // Source is ADC
    GPDMA_cfg.DstConn = 0;            // Destination is memory
    GPDMA_cfg.DMALLI = 0;             // No linked list

    GPDMA_SetUp(&GPDMA_cfg);    // Apply DMA configuration

    GPDMA_Init();               // Initialize the DMA module
}

void configure_timer_and_match(void)
{
    TIM_TIMERCFG_Type timer_cfg_struct; // Timer configuration struct variable
    TIM_MATCHCFG_Type match_cfg_struct; // Match configuration struct variable

    // Configure Timer0 in microsecond mode with a prescaler
    timer_cfg_struct.PrescaleOption = TIM_PRESCALE_USVAL; // Prescaler in microseconds
    timer_cfg_struct.PrescaleValue = T0_PRESCALE_VALUE; // Prescaler for 100 MHz clock -> 1 µs resolution

    TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &timer_cfg_struct); // Initialize Timer0 with the configuration

    // Configure match channel 0. Match0 will start an ADC conversion
    match_cfg_struct.MatchChannel = 0; // Match channel 0
    match_cfg_struct.IntOnMatch = ENABLE; // Enable interrupt on match  
    match_cfg_struct.StopOnMatch = DISABLE; // Do not stop on match 
    match_cfg_struct.ResetOnMatch = ENABLE; // Reset on match
    match_cfg_struct.ExtMatchOutputType = TIM_EXTMATCH_NOTHING; // Do nothing for external output pin if match  
    match_cfg_struct.MatchValue = T0_MATCH_VALUE; // Match value for ---. Match value formula is 
                                                // MatxhValue = desired time (seconds) / tick duration (seconds)

    TIM_ConfigMatch(LPC_TIM0, &match_cfg_struct); // Configure match channel 0
}

void start_timer(void)
{
    TIM_Cmd(LPC_TIM0, ENABLE); // Start Timer0  
}

void TIMER0_IRQHandler(void)
{
    // Clear match 0 interrupt
    TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT); // Clear interrupt

    start_ADC_conversion(); // Start ADC conversion 

}