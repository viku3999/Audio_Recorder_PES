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
 * @file    TPM.c
 * @brief   TPM module implementation
 * @author  Vishnu Kumar Thoodur Venkatachalapathy
 * @date    Dec 1, 2023
 */

#include "TPM.h"
#include "fsl_debug_console.h"
#include "ADC.h"
#include "Waveforms.h"
#include <stdbool.h>

uint32_t ADC_buff[1024];

bool TPM0_Flag = false, TPM1_Flag = false, TPM2_Flag = false;

int i=0;

/**
 * @brief		Initializes the TPM0 with the giveen mod value
 * @param[in]	mod_val -> value to be stored in the MOD register
 * @return		none
 */
void TPM0_Init(uint32_t mod_val){

	// Enable clk to TPM0
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;

	// select TPM clc source and set freq. to 48MHz
	SIM -> SOPT2 |= (SIM_SOPT2_TPMSRC(1)) | (SIM_SOPT2_PLLFLLSEL_MASK);

	// Loading the counter
	TPM0->MOD = TPM_MOD_MOD(mod_val);

	// Setting count direction to upwards and prescaler to 2
	TPM0->SC = TPM_SC_PS(0);

	// Generate an interrupt at end of counting
	TPM0->SC |= TPM_SC_TOIE_MASK;

	// Configure NVIC
	NVIC_SetPriority(TPM0_IRQn, 8); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(TPM0_IRQn);
	NVIC_EnableIRQ(TPM0_IRQn);

	// Enable DMA
//	TPM0->SC = TPM_SC_DMA(1);
}


/**
 * @brief		Initializes the TPM1 with the giveen mod value
 * @param[in]	mod_val -> value to be stored in the MOD register
 * @return		none
 */
void TPM1_Init(uint32_t mod_val){

	// Enable clk to TPM0
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;

	// select TPM clc source and set freq. to 48MHz
	SIM -> SOPT2 |= (SIM_SOPT2_TPMSRC(1)) | (SIM_SOPT2_PLLFLLSEL_MASK);

	// Loading the counter
	TPM1->MOD = TPM_MOD_MOD(mod_val);

	// Setting count direction to upwards and prescaler to 128
	TPM1->SC = TPM_SC_PS(7);

	// Generate an interrupt at end of counting
	TPM1->SC |= TPM_SC_TOIE_MASK;

	// Configure NVIC
	NVIC_SetPriority(TPM1_IRQn, 64); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(TPM1_IRQn);
	NVIC_EnableIRQ(TPM1_IRQn);
}


/**
 * @brief		Initializes the TPM1 with the giveen mod value
 * @param[in]	mod_val -> value to be stored in the MOD register
 * @return		none
 */
void TPM2_Init(uint32_t mod_val){

	// Enable clk to TPM0
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;

	// select TPM clc source and set freq. to 48MHz
	SIM -> SOPT2 |= (SIM_SOPT2_TPMSRC(1)) | (SIM_SOPT2_PLLFLLSEL_MASK);

	// Loading the counter
	TPM2->MOD = TPM_MOD_MOD(mod_val);

	// Setting count direction to upwards and prescaler to 128
	TPM2->SC = TPM_SC_PS(7);

	// Generate an interrupt at end of counting
	TPM2->SC |= TPM_SC_TOIE_MASK;

	// Configure NVIC
	NVIC_SetPriority(TPM2_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(TPM2_IRQn);
	NVIC_EnableIRQ(TPM2_IRQn);
}

/**
 * @brief	Function to start TPM0
 * @return	none
 */
void Start_TPM0() {
// Enable counter
	TPM0->SC |= TPM_SC_CMOD(1);
}


/**
 * @brief	Function to start TPM1
 * @return	none
 */
void Start_TPM1(){
// Enable counter
	TPM1->SC |= TPM_SC_CMOD(1);
}

/**
 * @brief	Function to start TPM2
 * @return	none
 */
void Start_TPM2(){
// Enable counter
	TPM2->SC |= TPM_SC_CMOD(1);
}


/**
 * @brief	Function to stop TPM0
 * @return	none
 */
void Stop_TPM0(){
	TPM0->SC &= ~TPM_SC_CMOD_MASK;
}


/**
 * @brief	Function to stop TPM1
 * @return	none
 */
void Stop_TPM1(){
	TPM1->SC &= ~TPM_SC_CMOD_MASK;
}

/**
 * @brief	Function to stop TPM2
 * @return	none
 */
void Stop_TPM2(){
	TPM2->SC &= ~TPM_SC_CMOD_MASK;
}

void Set_MOD_TPM0(uint32_t mod_val){
	// Loading the counter
	TPM0->MOD = TPM_MOD_MOD(mod_val);
}

void Set_MOD_TPM2(uint32_t mod_val){
	// Loading the counter
	TPM2->MOD = TPM_MOD_MOD(mod_val);
}

/**
 * @brief	TPM0 Interrupt handler
 * @return	none
 */
void TPM0_IRQHandler(){
	//clear pending IRQ
	NVIC_ClearPendingIRQ(TPM0_IRQn);
	TPM0_Flag = true;
	// Clear Interrupt flag
	TPM0->SC |= TPM_SC_TOF_MASK;
}

/**
 * @brief	TPM1 Interrupt handler
 * @return	none
 */
void TPM1_IRQHandler(){
	//clear pending IRQ
	NVIC_ClearPendingIRQ(TPM1_IRQn);

	// set TPM1_IRQ flag as true
	TPM1_Flag = true;

	// Clear Interrupt flag
	TPM1->SC |= TPM_SC_TOF_MASK;
}

/**
 * @brief	TPM1 Interrupt handler
 * @return	none
 */
void TPM2_IRQHandler(){
	//clear pending IRQ
	NVIC_ClearPendingIRQ(TPM2_IRQn);

	// set TPM1_IRQ flag as true
	TPM2_Flag = true;

	// Clear Interrupt flag
	TPM2->SC |= TPM_SC_TOF_MASK;
}
