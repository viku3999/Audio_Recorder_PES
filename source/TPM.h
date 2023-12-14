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
 * @file    TPM.h
 * @brief   Header file for TPM module implementation
 * @author  Vishnu Kumar Thoodur Venkatachalapathy
 * @date    Dec 12, 2023
 */

#ifndef TPM_H_
#define TPM_H_

#include "board.h"

extern bool TPM0_Flag, TPM1_Flag, TPM2_Flag;

extern uint32_t ADC_buff[1024];


/**
 * @brief		Initializes the TPM0 with the giveen mod value
 * @param[in]	mod_val -> value to be stored in the MOD register
 * @return		none
 */
void TPM0_Init(uint32_t mod_val);

/**
 * @brief		Initializes the TPM1 with the giveen mod value
 * @param[in]	mod_val -> value to be stored in the MOD register
 * @return		none
 */
void TPM1_Init(uint32_t mod_val);

/**
 * @brief		Initializes the TPM2 with the giveen mod value
 * @param[in]	mod_val -> value to be stored in the MOD register
 * @return		none
 */
void TPM2_Init(uint32_t mod_val);


/**
 * @brief	Function to start TPM0
 * @return	none
 */
void Start_TPM0();

/**
 * @brief	Function to start TPM1
 * @return	none
 */
void Start_TPM1();

/**
 * @brief	Function to start TPM2
 * @return	none
 */
void Start_TPM2();

/**
 * @brief	Function to stop TPM0
 * @return	none
 */
void Stop_TPM0();

/**
 * @brief	Function to stop TPM1
 * @return	none
 */
void Stop_TPM1();

/**
 * @brief	Function to start TPM2
 * @return	none
 */
void Stop_TPM2();
s
/**
 * @brief		Sets TPM0 with the given mod value
 * @param[in]	mod_val -> value to be stored in the MOD register
 * @return		none
 */
void Set_MOD_TPM0(uint32_t mod_val);

/**
 * @brief		Sets TPM2 with the given mod value
 * @param[in]	mod_val -> value to be stored in the MOD register
 * @return		none
 */
void Set_MOD_TPM2(uint32_t mod_val);

#endif /* TPM_H_ */
