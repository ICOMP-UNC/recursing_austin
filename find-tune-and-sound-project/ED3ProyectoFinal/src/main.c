/*
 * Copyright 2022 NXP
 * NXP confidential.
 * This software is owned or controlled by NXP and may only be used strictly
 * in accordance with the applicable license terms.  By expressly accepting
 * such terms or by downloading, installing, activating and/or otherwise using
 * the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to
 * be bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here
#include "system_logic.h"
#include "system_logic.c"

// TODO: insert other definitions and declarations here

int main(void) {

    // TODO: insert code here
	StatusFlags flags;
    flags.tuning_mode = CLEAR;  // Initialize the tuning mode flag
    flags.buffer_adc_full = CLEAR; // Initialize the buffer full flag

    while(TRUE) 
    {
        // Wait interrupts    
    }
    return 0 ;
}
