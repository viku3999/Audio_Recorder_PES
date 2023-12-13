/*
 * I2C_KL25Z.h
 *
 *  Created on: Dec 12, 2023
 *      Author: vishn
 */

#ifndef I2C_KL25Z_H_
#define I2C_KL25Z_H_

#include "board.h"

void Init_I2C();
uint8_t I2C_Read_Byte(uint8_t dev_addr, uint8_t data_addr);
void I2C_Busy_Wait();
void I2C_Repeat_Write_Setup(uint8_t dev_addr);
void I2C_Repeat_Write_Byte(uint8_t data);
void I2C_Stop();

#endif /* I2C_KL25Z_H_ */
