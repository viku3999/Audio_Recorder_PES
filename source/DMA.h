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
 * @brief   Header file for DAC module implementation
 * @author  Vishnu Kumar Thoodur Venkatachalapathy
 * @date    Dec 1, 2023
 */

#ifndef DMA_H_
#define DMA_H_

#include "board.h"


/**
 * @brief	Function to initialize the DMA module to transfer data whenever TPM0
 * 			overflows. Written by referencing dean's book
 * @return	none
 */
void Init_DMA();

/**
 * @brief	Sets the data source and number of bytes to transfer using DMA module
 * 			Written by referencing dean's book
 * @return	none
 */
void DMA_Set(uint16_t * src, uint32_t size);

/**
 * @brief	Starts DMA transfer using the set values
 * 			Written by referencing dean's book
 * @return	none
 */
void DMA_Start();


#endif /* DMA_H_ */
