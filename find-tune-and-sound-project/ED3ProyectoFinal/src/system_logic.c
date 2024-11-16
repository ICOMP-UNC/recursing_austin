#include "system_logic.h"

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

    // Configure DMA channel1 for memory-to-peripheral transfer
    GPDMA_cfg.ChannelNum = DMA_DAC_CHANNEL;         // Use channel 1
    GPDMA_cfg.SrcMemAddr = (uint32_t)table_waveform; // Source: DAC waveform table
    GPDMA_cfg.DstMemAddr = 0;         // No memory destination (peripheral)
    GPDMA_cfg.TransferSize = NUM_SAMPLES; // Transfer size: x samples
    GPDMA_cfg.TransferWidth = 0;      // Not used
    GPDMA_cfg.TransferType = GPDMA_TRANSFERTYPE_M2P; // Memory to peripheral - DMA control
    GPDMA_cfg.SrcConn = 0;            // Source is memory
    GPDMA_cfg.DstConn = GPDMA_CONN_DAC; // Destination is DAC
    GPDMA_cfg.DMALLI = (uint32_t)&DMA_LLI_struct; // Linked list for continuous transfer

    // Configure DMA Channel0 for peripheral (ADC) to memory transfer
    GPDMA_cfg.ChannelNum = DMA_ADC_CHANNEL;         // Use channel 0 (highest priority)
    GPDMA_cfg.SrcMemAddr = 0;         // No memory source (peripheral: ADC)
    GPDMA_cfg.DstMemAddr = (uint16_t)adc_buffer; // Destination: ADC buffer for sound analysis
    GPDMA_cfg.TransferSize = SIZE_BUFFER_ADC; // Transfer size:
    GPDMA_cfg.TransferWidth = 0;      // Not used
    GPDMA_cfg.TransferType = GPDMA_TRANSFERTYPE_P2M; // Peripheral to memory - DMA control
    GPDMA_cfg.SrcConn = GPDMA_CONN_ADC; // Source is ADC
    GPDMA_cfg.DstConn = 0;            // Destination is memory
    GPDMA_cfg.DMALLI = 0;             // No linked list
    // Terminal Count interupt already enabled in the driver implementation

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
                                                

    TIM_ConfigMatch(LPC_TIM0, &match_cfg_struct); // Configure match channel 0

    NVIC_EnableIRQ(TIMER0_IRQn); // Enable Timer0 interrupt in NVIC
}

void configure_external_interrupt(void)
{
    EXTI_InitTypeDef exti_cfg; // External interrupt configuration struct variable

    exti_cfg.EXTI_Line = EXTI_EINT0; // External interrupt line 0
    exti_cfg.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE; // Edge sensitive mode
    exti_cfg.EXTI_polarity = EXTI_POLARITY_LOW_ACTIVE_OR_FALLING_EDGE; // Low active or falling edge

    EXTI_Config(&exti_cfg); // Configure external interrupt

    NVIC_EnableIRQ(EINT0_IRQn); // Enable external interrupt in NVIC
}

void configure_adc(void)
{
    ADC_Init(LPC_ADC, ADC_FREQ); // Initialize ADC with a clock of 44.1 kHz
    ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_5, ENABLE); // Enable ADC channel 5
    ADC_BurstCmd(LPC_ADC, DISABLE); // Disable burst mode
    ADC_IntConfig(LPC_ADC, ADC_ADINTEN5, ENABLE); // Enable ADC interrupt for channel 5
    ADC_DMACmd(LPC_ADC, ENABLE); // Enable DMA for ADC
}

void start_timer(void)
{
    TIM_Cmd(LPC_TIM0, ENABLE); // Start Timer0  
}

void start_adc_conversion(void)
{
    NVIC_EnableIRQ(ADC_IRQn); // Enable ADC interrupt in NVIC
    ADC_StartCmd(LPC_ADC, ADC_START_NOW); // Start ADC conversion
}

void TIMER0_IRQHandler(void)
{
    // Clear match 0 interrupt
    TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT); // Clear interrupt

    start_adc_conversion(); // Start ADC conversion
}

// Overwrite the interrupt handle routine for EXTI0
void EINT0_IRQHandler(void)
{
    EXTI_ClearEXTIFlag(EXTI_EINT0); // Clear the interrupt flag

    if(status_flags.tuning_mode == 0)
    {
        status_flags.tuning_mode = 1; // Set tuning mode flag

        // Change the mode of operation
        start_timer(); // Start Timer0 to wait for ADC conversion
    }
    else
    {
        status_flags.tuning_mode = 0; // Clear tuning mode flag

        // Change the mode of operation to instrument mode
        //////////////////7
        //////////////////
        //////////////////
    }
}

void ADC_IRQHandler(void)
{
    NVIC_DisableIRQ(ADC_IRQn); // Disable ADC interrupt in NVIC
    
    if (ADC_ChannelGetStatus(LPC_ADC, ADC_CHANNEL_5, ADC_DATA_DONE) == SET)
    {
        // Read the ADC value
        adc_buffer[buffer_index] = ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL_5);
        // Update the buffer index to always store the latest value
        buffer_index = (buffer_index + 1) % SIZE_BUFFER_ADC;
    }

    NVIC_EnableIRQ(ADC_IRQn); // Enable ADC interrupt in NVIC
}

void DMA_IRQHandler(void)
{
    // Check the status of the DMA channel 0
    if (GPDMA_IntGetStatus(GPDMA_STAT_INT, DMA_ADC_CHANNEL))
    {
        // Clear the interrupt flag
        GPDMA_ClearIntPending(GPDMA_STATCLR_INTTC, DMA_ADC_CHANNEL);

        // Update the buffer full flag
        status_flags.buffer_adc_full = 1;

        // Call find_tune function for sound analysis
        find_tune(&adc_buffer, SIZE_BUFFER_ADC);
    }
}

