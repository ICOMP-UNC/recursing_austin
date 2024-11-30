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

// Boolean values definitions
#define TRUE 1
#define FALSE 0

// GPIO directions definitions
#define INPUT 0
#define OUTPUT 1

// Set - Clear definitions
#define SET 1
#define CLEAR 0s

#endif
