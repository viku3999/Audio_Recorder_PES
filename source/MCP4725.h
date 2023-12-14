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
 * @file    MCP4725.c
 * @brief   Headers for the I2C based drivers for the MCP4725 DAC
 * @author  Vishnu Kumar Thoodur Venkatachalapathy
 * @date    Dec 12, 2023
 */


#ifndef MCP4725_H_
#define MCP4725_H_

#include "board.h"
#include "I2C_KL25Z.h"

/**
 * @brief	Function to Test the DAC module by sending 0xFFF as the DAC o/p value
 * @return	none
 */
void Test();

/**
 * @brief		Sets only the onboard DAC with the given value using the fast
 * 				protocol given in the module data sheet
 * @param[in]	Value -> value to be write into the DAC
 * @return		none
 */
void Set_DAC_Fast(uint16_t Value);

/**
 * @brief		Sets only the onboard DAC with the given value using the
 * 				protocol given in the module data sheet
 * @param[in]	Value -> value to be write into the DAC
 * @return		none
 */
void Set_DAC(uint16_t Value);

/**
 * @brief		Sets the onboard DAC and EEPROM with the given value using the
 * 				protocol given in the module data sheet.
 * @param[in]	Value -> value to be write into the DAC and EEPROM
 * @return		none
 */
void Set_DAC_EEPROM(uint16_t Value);


#endif /* MCP4725_H_ */
