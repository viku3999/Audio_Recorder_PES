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
 * @file    I2C_KL25Z.c
 * @brief   I2C module implementation for the KL25Z dev board
 * @author  Vishnu Kumar Thoodur Venkatachalapathy
 * @date    Dec 12, 2023
 */

#ifndef I2C_KL25Z_H_
#define I2C_KL25Z_H_

#include "board.h"


/**
 * @brief	Initializes the onboard I2C peripherial at 100KHZ frequency
 * @return	none
 */
void Init_I2C();

/**
 * @brief	Sends the Start	condition on the I2C bus and sets the
 * 			microcontroller in Transmission mode
 * @return	none
 */
void I2C_Start_Tx();


/**
 * @brief		Sends the Re-Start condition on the I2C bus, Transmitts the given device address
 *	 			and sets the microcontroller in Recieve mode.
 * @param[in]	dev_addr -> Device address from which we should get data from
 * @return	none
 */
void I2C_Start_Rx(uint8_t dev_addr);


/**
 * @brief		Reads the data from the specified address location from the
 * 				given device ID on the I2C bus
 * @param[in]	dev_addr -> Device address from which we should get the data from
 * 				data_addr -> Address on the device from which we should get the
 * 							 data from
 * @return		data recieved from the I2C device
 */
uint8_t I2C_Read_Byte(uint8_t dev_addr, uint8_t data_addr);

/**
 * @brief	Waits till a Transmission is completed
 * @return	none
 */
void I2C_Busy_Wait();

/**
 * @brief		Sets-up the I2C bus for a repeated write transmission.
 * 				Sends the Start condition, and the given device address in
 * 				write mode
 * @param[in]	dev_addr -> Device address from which we should get data from
 * @return	none
 */
void I2C_Repeat_Write_Setup(uint8_t dev_addr);

/**
 * @brief		Send the given data on the I2C bus (for the Repeat_write type
 * 				transmission)
 * @param[in]	data -> data to send on the I2C bus
 * @return	none
 */
void I2C_Repeat_Write_Byte(uint8_t data);

/**
 * @brief		Writes the given data on the I2C bus for the specified device
 * 				ID and address location
 * @param[in]	dev_addr -> Device address to which we should write the data
 * 				data_addr -> Address on the device to which we should write the
 * 							 given data
 * 				data -> data to send on the I2C bus to the device
 * @return	none
 */
void I2C_Write_Byte(uint8_t dev_addr, uint8_t data_addr, uint8_t data);

/**
 * @brief	Sends the Stop condition on the I2C bus
 * @return	none
 */
void I2C_Stop();

#endif /* I2C_KL25Z_H_ */
