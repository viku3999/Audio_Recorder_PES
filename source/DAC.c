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
 * @file    DAC.c
 * @brief   DAC module implementation
 * @author  Vishnu Kumar Thoodur Venkatachalapathy
 * @date    Dec 1, 2023
 */

#include <DAC.h>

#define DAC_Pin (30)

/**
 * @brief	Function to initialize the DAC module. Written by referencing dean's book
 * @return	none
 */
void DAC_Init(){

	// Enable clk to DAC and port E
	SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

	// Select Analog pin
	PORTE->PCR[DAC_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[DAC_Pin] |= PORT_PCR_MUX(0);

	//Disable buffer mode
	DAC0->C1 = 0;
	DAC0->C2 = 0;

	//Enable DAC and select VDDA as ref.
	DAC0->C0 = DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK;

}

/**
 * @brief		Sets the DAC value with the given value.
 * @param[in]	x -> DAC value to set, which should be between 0-4095
 * @return		-1: if given value is not in range of 0-4096, 1: if DAC is set
 * 				successfully
 */
int DAC_SetVal(int x){
	if(x < 0)
		return -1;
	if(x > 4095)
		return -1;

	DAC0->DAT[0].DATL = DAC_DATL_DATA0(x);
	DAC0->DAT[0].DATH = DAC_DATH_DATA1(x>>8);

	return 1;
}
