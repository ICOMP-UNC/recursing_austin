#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif


#include "lpc17xx_gpio.h"    /* GPIO handling */
#include "lpc17xx_pinsel.h"  /* Pin function selection */
#include "lpc17xx_systick.h" /* SysTick handling */
#include "lpc17xx_timer.h"   /* Timer handling*/
#include "lpc17xx_dac.h"
#include "lpc17xx_gpdma.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_i2c.h"
#include "lcd.h"
#include "system_logic.h"


void EINT3_IRQHandler (void)
{
    if ((~GPIO_ReadValue(PINSEL_PORT_0) & KEYS_MASK) == ((uint32_t) 0x00) )
    {
        GPDMA_ChannelCmd(DMA_CHANNEL_0, DISABLE);
        DAC_UpdateValue(LPC_DAC, DAC_VALUE_OFFSET);
    }
    else 
    {
        if (~GPIO_ReadValue(PINSEL_PORT_0) & KEY_DO)   //DO note
        {
            DAC_update_count_value (FREQUENCY_DO);
            GPDMA_ChannelCmd(DMA_CHANNEL_0, ENABLE);
        }
        else if (~GPIO_ReadValue(PINSEL_PORT_0) & KEY_REb)   //REb note
        {
            DAC_update_count_value (FREQUENCY_REb);
            GPDMA_ChannelCmd(DMA_CHANNEL_0, ENABLE);
        }
        else if (~GPIO_ReadValue(PINSEL_PORT_0) & KEY_RE)   //RE note
        {
            DAC_update_count_value (FREQUENCY_RE);
            GPDMA_ChannelCmd(DMA_CHANNEL_0, ENABLE);
        }
        else if (~GPIO_ReadValue(PINSEL_PORT_0) & KEY_MIb)    //MIb note
        {
            DAC_update_count_value (FREQUENCY_MIb);
            GPDMA_ChannelCmd(DMA_CHANNEL_0, ENABLE);
        }
        else if (~GPIO_ReadValue(PINSEL_PORT_0) & KEY_MI)    //MI note
        {
            DAC_update_count_value (FREQUENCY_MI);
            GPDMA_ChannelCmd(DMA_CHANNEL_0, ENABLE);
        }
        else if (~GPIO_ReadValue(PINSEL_PORT_0) & KEY_FA)    //FA note
        {
            DAC_update_count_value (FREQUENCY_FA);
            GPDMA_ChannelCmd(DMA_CHANNEL_0, ENABLE);
        }
        else if (~GPIO_ReadValue(PINSEL_PORT_0) & KEY_SOLb)   //SOLb note
        {
            DAC_update_count_value (FREQUENCY_SOLb);
            GPDMA_ChannelCmd(DMA_CHANNEL_0, ENABLE);
        }
        else if (~GPIO_ReadValue(PINSEL_PORT_0) & KEY_SOL)   //SOL note
        {
            DAC_update_count_value (FREQUENCY_SOL);
            GPDMA_ChannelCmd(DMA_CHANNEL_0, ENABLE);
        }
        else if (~GPIO_ReadValue(PINSEL_PORT_0) & KEY_LAb)   //LAb note
        {
            DAC_update_count_value (FREQUENCY_LAb);
            GPDMA_ChannelCmd(DMA_CHANNEL_0, ENABLE);
        }
        else if (~GPIO_ReadValue(PINSEL_PORT_0) & KEY_LA)    //LA note
        {
            DAC_update_count_value (FREQUENCY_LA);
            GPDMA_ChannelCmd(DMA_CHANNEL_0, ENABLE);
        }
        else if (~GPIO_ReadValue(PINSEL_PORT_0) & KEY_SIb)   //SIb note
        {
            DAC_update_count_value (FREQUENCY_SIb);
            GPDMA_ChannelCmd(DMA_CHANNEL_0, ENABLE);
        }
        else if (~GPIO_ReadValue(PINSEL_PORT_0) & KEY_SI)   //SI note
        {
            DAC_update_count_value (FREQUENCY_SI);
            GPDMA_ChannelCmd(DMA_CHANNEL_0, ENABLE);
        }
    }
}

void DAC_update_count_value (uint32_t frequency)
{
    uint32_t update_value;
    update_value = (CLOCK_DAC_MHZ * 1000000)/(frequency * NUM_SAMPLES);
    DAC_SetDMATimeOut(LPC_DAC, update_value);
}
