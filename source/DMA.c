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
 * @file    DMA.c
 * @brief   DAC module implementation
 * @author  Vishnu Kumar Thoodur Venkatachalapathy
 * @date    Dec 1, 2023
 */
#include "DMA.h"

#include "fsl_debug_console.h"

uint16_t * Reload_DMA_Source=0;
uint32_t Reload_DMA_Byte_Count=0;

/**
 * @brief	Function to initialize the DMA module to transfer data whenever TPM0
 * 			overflows. Written by referencing dean's book
 * @return	none
 */
void Init_DMA(){
	// Gate clocks to DMA and DMAMUX
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

	// Disable DMA channel to allow configuration
	DMAMUX0->CHCFG[0] = 0;

	// Increment source, transfer words (16 bits)
	// Enable peripheral request, and
	// Generate DMA interrupt when done
	DMA0->DMA[0].DCR =	DMA_DCR_EINT_MASK | DMA_DCR_SINC_MASK |
						DMA_DCR_SSIZE(2) | DMA_DCR_DSIZE(2) |
						DMA_DCR_ERQ_MASK | DMA_DCR_CS_MASK;

	// Configure NVIC for DMA ISR
	NVIC_SetPriority(DMA0_IRQn, 3);
	NVIC_ClearPendingIRQ(DMA0_IRQn);
	NVIC_EnableIRQ(DMA0_IRQn);

	// Enable DMA MUX channel with TPM0 overflow as trigger
	DMAMUX0->CHCFG[0] = DMAMUX_CHCFG_SOURCE(54);
}

/**
 * @brief	Sets the data source and number of bytes to transfer using DMA module
 * 			Written by referencing dean's book
 * @return	none
 */
void DMA_Set(uint16_t * src, uint32_t size){
	Reload_DMA_Source = src;
	Reload_DMA_Byte_Count = size;
}


/**
 * @brief	Starts DMA transfer using the set values
 * 			Written by referencing dean's book
 * @return	none
 */
void DMA_Start(){

	// Set the source for DMA as per the value given in the "DMA_Set" function
	// and the destination as the DAC0 DAT register
	DMA0->DMA[0].SAR = DMA_SAR_SAR((uint32_t) Reload_DMA_Source);
	DMA0->DMA[0].DAR = DMA_DAR_DAR((uint32_t) (&(DAC0->DAT[0])));

	// number of byte to transfer (we are multipling by two since we have to
	// set data high and low registers in the DAC
	DMA0->DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(Reload_DMA_Byte_Count*2);

	// clear done flag
	DMA0->DMA[0].DSR_BCR &= ~DMA_DSR_BCR_DONE_MASK;

	// set enable flag
	DMAMUX0->CHCFG[0] |= DMAMUX_CHCFG_ENBL_MASK;
}

/**
 * @brief	DMA Interrupt handeler
 * @return	none
 */
void DMA0_IRQHandler(void) {
	// Clear done flag
	DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;

	// re-start DMA transfer
	DMA_Start();
}
