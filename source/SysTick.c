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
 * @file    SysTick.h
 * @brief   Function definition required for implementing SysTick
 * @author  Vishnu Kumar Thoodur Venkatachalapathy
 * @date    Dec 1, 2023
 */

#include "fsl_device_registers.h"
#include "DMA.h"
#include "TPM.h"
#include "Waveforms.h"


uint16_t * sq_Source=0;
uint16_t * sine_Source=0;
uint16_t * tri_Source=0;
uint32_t sq_Byte_Count=0, sine_Byte_Count=0, tri_Byte_Count=0;
int x=0;

/**
 * @brief	Setups the SysTick module to generate an interrupt every 2s
 *			(developed by referencing deans' book, chapter 7,
 * 			Listing 7.1
 *
 * @return  none
 */
void init_SysTick(){
	SysTick -> LOAD = 6000000;
	NVIC_SetPriority (SysTick_IRQn, 2);
	SysTick -> VAL = 0;
	SysTick -> CTRL = SysTick_CTRL_TICKINT_Msk;
}

/**
 * @brief	Function to save the waveform buffer data and loop between the 3 waveforms
 * @return	none
 */
void SysTick_Set(uint16_t * sq_src, uint32_t sq_size, uint16_t * sine_src, uint32_t sine_size, uint16_t * tri_src, uint32_t tri_size){
	sq_Source = sq_src;
	sq_Byte_Count = sq_size;

	sine_Source = sine_src;
	sine_Byte_Count = sine_size;

	tri_Source = tri_src;
	tri_Byte_Count = tri_size;

	// Set x=0 to loop through the given 3 waveforms
	x=0;
}

/**
 * @brief	Function to save 1 waveform buffer data
 * @return	none
 */
void SysTick_Set_2(uint16_t * Sine_src, uint32_t Sine_size){
	sine_Source = Sine_src;
	sine_Byte_Count = Sine_size;

	// Set x=4 to generate only the given waveform
	x = 4;
}

/**
 * @brief	Function to waveform genertion at DAC pin
 * @return	none
 */
void SysTick_Start(){

	// Set the source for the DMA to copy data from
	if(x==0){
		DMA_Set(sq_Source, sq_Byte_Count);

		// set x=1 to make the DMA to reffer the next waveform
		x=1;
	}
	else if(x == 1){
		DMA_Set(sine_Source, sine_Byte_Count);

		// set x=2 to make the DMA to reffer the next waveform
		x=2;
	}
	else if(x == 2){
		DMA_Set(tri_Source, tri_Byte_Count);

		// set x=0 to make the DMA to reffer the next waveform
		x=0;
	}
	else if(x == 4){
		DMA_Set(sine_Source, sine_Byte_Count);
	}

	// Start DMA copy
	DMA_Start();

	// Initialize TPM0 at 96KHz and start TPM0
	TPM0_Init(500);
	Start_TPM0();

	// Start SysTick module
	SysTick -> CTRL |= SysTick_CTRL_ENABLE_Msk;

	//Get the waveform input
	Waveform_IP();
}

/**
 * @brief	SysTick interrupt function definition Increments the common and
 * 			function specific counters and sets the appropriate flag
 *
 * @return	none
 */
void SysTick_Handler(){
	Stop_TPM0();

	// Restart wave generation
	SysTick_Start();
}
