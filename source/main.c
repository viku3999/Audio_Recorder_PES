/*******************************************************************************
 * Copyright (C) 2023 by Vishnu Kumar Thoodur Venkatachalapathy
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Vishnu Kumar Thoodur Venkatachalapathy and the University of
 * Colorado are not liable for any misuse of this material.
 * ****************************************************************************/

/**
 * @file    main.c
 * @brief   Implementation of the funciton wave generator
 * @author  Vishnu Kumar Thoodur Venkatachalapathy
 * @date    Dec 1, 2023
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "pin_mux.h"
#include "test_sine.h"

#include <stdio.h>
#include "DAC.h"
#include "Waveforms.h"
#include "DMA.h"
#include "TPM.h"
#include "SysTick.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*
 * @brief Main function
 */
int main(void)
{
	/* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\nPES Assignment 7: Waveforms\r\n");

    test_sin();

    // Initializing required peripherals
    Init_DMA();
    DAC_Init();
    init_SysTick();

    //Starting wave genration
	Start_Wave_Generation();

    while (1)
    {
    	// Checking if TPM1 flag is set and collecting ADC samples
    	if(flag)
    		analyze();
    }
}
