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
 * @file    Waveforms.h
 * @brief   Header file for waveform generation functions
 * @author  Vishnu Kumar Thoodur Venkatachalapathy
 * @date    Dec 1, 2023
 */

#ifndef WAVEFORMS_H_
#define WAVEFORMS_H_

#include "fp_trig.h"

#define num_samples 96000
#define BUFFER_SIZE 1024

/**
 * @brief		Generates a square wave buffer using which the DAC can generate a
 * 				Square wave at the specified frequency and time
 * @param[in]	period -> time period in seconds for which the wave must
 * 				be geenrated
 * @return		none
 */
void SQ_Wave(float period);

/**
 * @brief		Generates a sine wave buffer using which the DAC can generate a
 * 				sine wave at the specified frequency and time
 * @param[in]	period -> time period in seconds for which the wave must
 * 				be geenrated
 * @return		none
 */
void Sine_Wave(float period);

/**
 * @brief		Generates a triangle wave buffer using which the DAC can generate a
 * 				triangle wave at the specified frequency and time
 * @param[in]	period -> time period in seconds for which the wave must
 * 				be geenrated
 * @return		none
 */
void Tri_Wave(float period);

/**
 * @brief	Function to start the waveform generation
 * @return	none
 */
void Start_Wave_Generation();

/**
 * @brief	Function to analyse the generated waveform
 * @return	none
 */
void Waveform_Analyze();

/**
 * @brief	Function to start the input sampling
 * @return	none
 */
void Waveform_IP();
#endif /* WAVEFORMS_H_ */
