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
 * @brief   Function prototypes required for implementing SysTick
 * @author  Vishnu Kumar Thoodur Venkatachalapathy
 * @date    Dec 1, 2023
 */


#ifndef SYSTICK_H_
#define SYSTICK_H_

/**
 * @brief	Setups the SysTick module to generate an interrupt every 2s
 *			(developed by referencing deans' book, chapter 7,
 * 			Listing 7.1
 *
 * @return  none
 */
void init_SysTick();

/**
 * @brief	Function to save the waveform buffer data and loop between the 3 waveforms
 * @return	none
 */
void SysTick_Set(uint16_t * sq_src, uint32_t sq_size, uint16_t * sine_src, uint32_t sine_size, uint16_t * tri_src, uint32_t tri_size);

/**
 * @brief	Function to save 1 waveform buffer data
 * @return	none
 */
void SysTick_Set_2(uint16_t * Sine_src, uint32_t Sine_size);

/**
 * @brief	Function to waveform genertion at DAC pin
 * @return	none
 */
void SysTick_Start();

#endif /* SYSTICK_H_ */
