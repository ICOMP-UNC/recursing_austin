#include "adc_i2c_gpio_config.h"

//Functions definitions

void configure_gpio (void)
{
    PINSEL_CFG_Type pin_cfg;

    pin_cfg.Portnum = PINSEL_PORT_0;
    pin_cfg.Funcnum = PINSEL_FUNC_0;
    pin_cfg.Pinmode = PINSEL_PINMODE_PULLUP;
    pin_cfg.OpenDrain = PINSEL_PINMODE_NORMAL;

    pin_cfg.Pinnum = PINSEL_PIN_0;     //DO note on P0.0
    PINSEL_ConfigPin(&pin_cfg);

    pin_cfg.Pinnum = PINSEL_PIN_1;     //REb note on P0.1
    PINSEL_ConfigPin(&pin_cfg);

    pin_cfg.Pinnum = PINSEL_PIN_2;     //RE note on P0.2
    PINSEL_ConfigPin(&pin_cfg);

    pin_cfg.Pinnum = PINSEL_PIN_3;     //MIb note on P0.3
    PINSEL_ConfigPin(&pin_cfg);

    pin_cfg.Pinnum = PINSEL_PIN_4;     //MI note on P0.4
    PINSEL_ConfigPin(&pin_cfg);

    pin_cfg.Pinnum = PINSEL_PIN_5;     //FA note on P0.5
    PINSEL_ConfigPin(&pin_cfg);

    pin_cfg.Pinnum = PINSEL_PIN_6;     //SOLb note on P0.6
    PINSEL_ConfigPin(&pin_cfg);

    pin_cfg.Pinnum = PINSEL_PIN_7;     //SOL note on P0.7
    PINSEL_ConfigPin(&pin_cfg);

    pin_cfg.Pinnum = PINSEL_PIN_8;     //LAb noteon P0.8
    PINSEL_ConfigPin(&pin_cfg);

    pin_cfg.Pinnum = PINSEL_PIN_9;     //LA note on P0.9
    PINSEL_ConfigPin(&pin_cfg);

    pin_cfg.Pinnum = PINSEL_PIN_10;    //SIb note on P0.10
    PINSEL_ConfigPin(&pin_cfg);

    pin_cfg.Pinnum = PINSEL_PIN_11;    //SI note on P0.11
    PINSEL_ConfigPin(&pin_cfg);

    //Set direction of P.0 to P.11 as input
    GPIO_SetDir(PINSEL_PORT_0, KEY_DO | KEY_REb | KEY_RE | KEY_MIb | KEY_MI | KEY_FA | KEY_SOLb | KEY_SOL | KEY_LAb | KEY_LA | KEY_SIb | KEY_SI ,INPUT);
    //Enable the interrupt on rising edge
    GPIO_IntCmd(PINSEL_PORT_0, KEY_DO | KEY_REb | KEY_RE | KEY_MIb | KEY_MI | KEY_FA | KEY_SOLb | KEY_SOL | KEY_LAb | KEY_LA | KEY_SIb | KEY_SI ,EDGE_RISIING);
    //Enable the interrupt on falling edge
    GPIO_IntCmd(PINSEL_PORT_0, KEY_DO | KEY_REb | KEY_RE | KEY_MIb | KEY_MI | KEY_FA | KEY_SOLb | KEY_SOL | KEY_LAb | KEY_LA | KEY_SIb | KEY_SI ,EDGE_FALLING);
}


void configure_adc(void)
{
    PINSEL_CFG_Type adc_pin_cfg;
    adc_pin_cfg.Portnum = PINSEL_PORT_0;        
    adc_pin_cfg.Pinnum = PINSEL_PIN_25;         //ADC input on P0.25 (ADC channel 0)
    adc_pin_cfg.Funcnum = PINSEL_FUNC_1;        //ADC function
    adc_pin_cfg.Pinmode = PINSEL_PINMODE_TRISTATE;     //No pull-up nor pull_down
    adc_pin_cfg.OpenDrain = PINSEL_PINMODE_NORMAL;     //No opendrain mode

    PINSEL_ConfigPin(&adc_pin_cfg);

    ADC_Init(LPC_ADC,ADC_SAMPLE_RATE);
    ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_2,ENABLE);
}


void configure_i2c(void)
{
    //SDA1 function on P0.19 pin
    PINSEL_CFG_Type i2c_pin_cfg;
    i2c_pin_cfg.Portnum = PINSEL_PORT_0;
    i2c_pin_cfg.Pinnum = PINSEL_PIN_19;
    i2c_pin_cfg.Funcnum = PINSEL_FUNC_3;
    i2c_pin_cfg.Pinmode = PINSEL_PINMODE_TRISTATE;
    i2c_pin_cfg.OpenDrain = PINSEL_PINMODE_OPENDRAIN;

    PINSEL_ConfigPin(&i2c_pin_cfg);

    //SCL1 function on P0.20 pin
    i2c_pin_cfg.Pinnum = PINSEL_PIN_20;
    i2c_pin_cfg.Funcnum = PINSEL_FUNC_3;
    i2c_pin_cfg.Pinmode = PINSEL_PINMODE_TRISTATE;
    i2c_pin_cfg.OpenDrain = PINSEL_PINMODE_OPENDRAIN;

    PINSEL_ConfigPin(&i2c_pin_cfg);

    I2C_Init(LPC_I2C1, I2C_FREQ);
    I2C_Cmd(LPC_I2C1, I2C_MASTER_MODE, ENABLE);
    
}