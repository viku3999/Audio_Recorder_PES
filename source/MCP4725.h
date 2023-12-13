/*
 * MCP4725.h
 *
 *  Created on: Dec 13, 2023
 *      Author: vishn
 */

#ifndef MCP4725_H_
#define MCP4725_H_

#include "board.h"
#include "I2C_KL25Z.h"

void Test();

void Set_DAC_Fast(uint16_t Value);

void Set_DAC(uint16_t Value);

void Set_DAC_EEPROM(uint16_t Value);


#endif /* MCP4725_H_ */
