/*
 * @file main.c
 * @brief Main file for the project
 */
#ifndef SYSTEM_LOGIC_H
#define SYSTEM_LOGIC_H


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

/*Pin definitions*/
#define KEY_DO   ((uint32_t)(1 << 0))    /*Key DO conectado al P0.0*/
#define KEY_REb  ((uint32_t)(1 << 1))    /*Key REb conectado al P0.1*/
#define KEY_RE   ((uint32_t)(1 << 2))    /*Key RE conectado al P0.2*/
#define KEY_MIb  ((uint32_t)(1 << 3))    /*Key MIb conectado al P0.3*/
#define KEY_MI   ((uint32_t)(1 << 4))    /*Key MI conectado al P0.4*/
#define KEY_FA   ((uint32_t)(1 << 5))    /*Key FA conectado al P0.5*/
#define KEY_SOLb ((uint32_t)(1 << 6))    /*Key SOLb conectado al P0.6*/
#define KEY_SOL  ((uint32_t)(1 << 7))    /*Key SOL conectado al P0.7*/
#define KEY_LAb  ((uint32_t)(1 << 8))    /*Key LAb conectado al P0.8*/
#define KEY_LA   ((uint32_t)(1 << 9))    /*Key LA conectado al P0.9*/
#define KEY_SIb  ((uint32_t)(1 << 10))   /*Key SIb conectado al P0.10*/
#define KEY_SI   ((uint32_t)(1 << 11))   /*Key SI conectado al P0.11*/

#define FREQUENCY_DO   261.626      /*Frequency of DO note in Hz*/
#define FREQUENCY_REb  277.183      /*Frequency of REb note in Hz*/
#define FREQUENCY_RE   293.665      /*Frequency of RE note in Hz*/
#define FREQUENCY_MIb  311.127      /*Frequency of MIb note in Hz*/
#define FREQUENCY_MI   329.628      /*Frequency of MI note in Hz*/
#define FREQUENCY_FA   349.228      /*Frequency of FA note in Hz*/
#define FREQUENCY_SOLb 369.994      /*Frequency of SOLb note in Hz*/
#define FREQUENCY_SOL  391.995      /*Frequency of SOL note in Hz*/
#define FREQUENCY_LAb  415.305      /*Frequency of LAb note in Hz*/
#define FREQUENCY_LA   440          /*Frequency of LA note in Hz*/
#define FREQUENCY_SIb  466.164      /*Frequency of SIb note in Hz*/
#define FREQUENCY_SI   493.883      /*Frequency of SI note in Hz*/

#define KEYS_MASK      ((uint32_t) 0xFFF)   /*12 notes input mask*/

#define NUM_SAMPLES   64            /*Number of samples to create a sin waveform*/
#define CLOCK_DAC_MHZ 25            /*DAC clock in MHz*/

#define DMA_CHANNEL_0 0

#define DAC_VALUE_OFFSET 511        /*Offset value of DAC */    
#define ADC_SAMPLE_RATE 44100       /*ADC sample rate in Hz*/

#define I2C_FREQ 100000             /*I2C frequency*/

#define RISING_EDGE 0
#define FALLING_EDGE 1


const uint16_t sin_table64 [64] = {
    511, 561, 611, 659, 707, 752, 795, 835, 872, 906, 936, 962, 983, 1000, 1012, 1020, 1022
    1020, 1012, 1000, 983, 962, 936, 906, 872, 835, 795, 752, 707, 659, 611, 561, 511, 461
    411, 363, 315, 270, 227, 187, 150, 116, 86, 60, 39, 22, 10, 2, 0, 2, 10, 22, 39, 60, 86
    116, 150, 187, 227, 270, 315, 363, 411, 461 
};

I2C_M_SETUP_Type M_i2c_config;

typedef enum
{
    DO_NOTE,
    REb_NOTE,
    RE_NOTE,
    MIb_NOTE,
    MI_NOTE,
    FA_NOTE,
    SOLb_NOTE,
    SOL_NOTE,
    LAb_NOTE,
    LA_NOTE,
    SIb_NOTE,
    SI_NOTE
} Notes;

void EINT3_IRQHandler(void);

void DAC_update_count_value (uint32_t frequency);

#endif