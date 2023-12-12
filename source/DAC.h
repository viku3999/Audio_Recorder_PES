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
 * @brief   Header file for DAC module implementation
 * @author  Vishnu Kumar Thoodur Venkatachalapathy
 * @date    Dec 1, 2023
 */
#ifndef DAC_H_
#define DAC_H_

#include "board.h"

/**
 * @brief	Function to initialize the DAC module. Written by referencing dean's book
 * @return	none
 */
void DAC_Init();

/**
 * @brief		Sets the DAC value with the given value.
 * @param[in]	x -> DAC value to set, which should be between 0-4095
 * @return		-1: if given value is not in range of 0-4096, 1: if DAC is set
 * 				successfully
 */
int DAC_SetVal(int x);

#endif /* DAC_H_ */
