#include "LPC17xx.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"

/*Pin definitions*/
#define KEY_DO   ((uint32_t)(1 << 0))    /*Key DO connected al P0.0*/
#define KEY_REb  ((uint32_t)(1 << 1))    /*Key REb connected al P0.1*/
#define KEY_RE   ((uint32_t)(1 << 2))    /*Key RE connected al P0.2*/
#define KEY_MIb  ((uint32_t)(1 << 3))    /*Key MIb connected al P0.3*/
#define KEY_MI   ((uint32_t)(1 << 4))    /*Key MI connected al P0.4*/
#define KEY_FA   ((uint32_t)(1 << 5))    /*Key FA connected al P0.5*/
#define KEY_SOLb ((uint32_t)(1 << 6))    /*Key SOLb connected al P0.6*/
#define KEY_SOL  ((uint32_t)(1 << 7))    /*Key SOL connected al P0.7*/
#define KEY_LAb  ((uint32_t)(1 << 8))    /*Key LAb connected al P0.8*/
#define KEY_LA   ((uint32_t)(1 << 9))    /*Key LA connected al P0.9*/
#define KEY_SIb  ((uint32_t)(1 << 10))   /*Key SIb connected al P0.10*/
#define KEY_SI   ((uint32_t)(1 << 11))   /*Key SI connected al P0.11*/

#define ADC_SAMPLE_RATE 44100            /*ADC sample rate in Hz*/

#define I2C_FREQ 100000                  /*I2C frequency in Hz*/
//Functions prototypes

/**
 * @brief Configure P0.0 to P0.11 for GPIO function 
 * 
 */
void configure_gpio(void);

/**
 * @brief Configure ADC peripheral
 * 
 */
void configure_adc(void);

/**
 * @brief Configure I2C1 peripheral 
 * 
 */
void configure_i2c(void);