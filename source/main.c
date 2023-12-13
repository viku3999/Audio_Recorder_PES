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
#include "I2C_KL25Z.h"
#include "MCP4725.h"

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

//    test_sin();

    // Initializing required peripherals
//    Init_DMA();
//    DAC_Init();
//    init_SysTick();

    //Starting wave genration
//	Start_Wave_Generation();

//    uint8_t Data=0;

//    Test();
	Init_I2C();
//	Set_DAC_Fast(0x000);
//	Set_DAC(0x000);
//	Set_DAC_EEPROM(0x0FF);
    while (1)
    {
    	for(uint16_t i=0; i<4096; i++){
    		Set_DAC(i);
    		for(int j=0; j<10000; j++);
    	}

    	for(uint16_t i=4095; i>=0; i--){
			Set_DAC(i);
			for(int j=0; j<10000; j++);
		}
//    	Data = I2C_Read_Byte(0x62, );
//    	if(Data != 0){
//			PRINTF("Got: %d", Data);
//			Data = 0;
//    	}
    }
}
