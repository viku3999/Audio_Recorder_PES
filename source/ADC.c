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
 * @file    ADC.c
 * @brief   ADC module implementation
 * @author  Vishnu Kumar Thoodur Venkatachalapathy
 * @date    Dec 1, 2023
 */

#include "ADC.h"


/**
 * @brief	Function to initialize the ADC module. Written by referencing dean's book
 * @return	none
 */
void init_ADC0(){
	// Enable clk to ADC0 and respective pin
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;

	// long sample time,
	// 16 bit single-ended conversion, bus clock input
	ADC0->CFG1 = ADC_CFG1_ADLSMP_MASK |
				 ADC_CFG1_MODE(3) | ADC_CFG1_ADICLK(0);

	// Software trigger, compare function disabled,
	// DMA disabled, voltage references VREFH and VREFL
	ADC0->SC2 = ADC_SC2_REFSEL(0);
}
