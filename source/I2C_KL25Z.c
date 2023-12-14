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

#include "I2C_KL25Z.h"

#define I2C_WRITE (0<<0)
#define I2C_READ (1<<0)


/**
 * @brief	Initializes the onboard I2C peripherial at 100KHZ frequency
 * @return	none
 */
void Init_I2C(){
	// I2C Configs
	// Enable clk to I2C
	SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;

	// Setting As master and I2C Baud rate to 100KHz. Mul -> 4, divider -> 0
	I2C1->F = (0x2 << I2C_F_MULT_SHIFT) | (0x00 << I2C_F_ICR_SHIFT);

	//Enable I2C module
	I2C1->C1 |= I2C_C1_IICEN_MASK | I2C_C1_IICIE_MASK;

	// Select high drive???
	I2C1->C2 |= I2C_C2_HDRS_MASK;
	//Init RAM variables for Tx data (IICEN = 1, IICIE = 1)

	// GPIO Config
	//Enable clk to Port E for the I2C pins
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	PORTE->PCR[0] |= PORT_PCR_MUX(6); // PE0 -> SDA
	PORTE->PCR[1] |= PORT_PCR_MUX(6); // PE1 -> SCL
}

/**
 * @brief	Sends the Start	condition on the I2C bus and sets the
 * 			microcontroller in Transmission mode
 * @return	none
 */
void I2C_Start_Tx(){
	I2C1->C1 |= I2C_C1_TX_MASK; // Set Transmission Mode
	I2C1->C1 |= I2C_C1_MST_MASK;
}

/**
 * @brief		Sends the Re-Start condition on the I2C bus, Transmitts the given device address
 *	 			and sets the microcontroller in Recieve mode.
 * @param[in]	dev_addr -> Device address from which we should get data from
 * @return	none
 */
void I2C_Start_Rx(uint8_t dev_addr){

	I2C1->C1 |= I2C_C1_RSTA_MASK; // Sending Re-Start command
	I2C1->D = (dev_addr<<1)|I2C_READ;
	I2C_Busy_Wait();

	I2C1->C1 &= ~I2C_C1_TX_MASK;
	I2C_Busy_Wait();
}


/**
 * @brief	Sends the Stop condition on the I2C bus
 * @return	none
 */
void I2C_Stop(){
	I2C1->C1 &= ~I2C_C1_MST_MASK;
}

/**
 * @brief	Waits till a Transmission is completed
 * @return	none
 */
void I2C_Busy_Wait(){

	// Wait till the IICIF bit is high or the TCF bit is high
	while(((I2C1->S & I2C_S_IICIF_MASK)==0) || ((I2C1->S & I2C_S_TCF_MASK) == 0));

	// Clear the S register by reading data from it
	I2C1->S |= 1<<I2C_S_IICIF_SHIFT;
}

/**
 * @brief		Sets-up the I2C bus for a repeated write transmission.
 * 				Sends the Start condition, and the given device address in
 * 				write mode
 * @param[in]	dev_addr -> Device address from which we should get data from
 * @return	none
 */
void I2C_Repeat_Write_Setup(uint8_t dev_addr){
	I2C_Start_Tx();
	// Send the device ID
	I2C1->D = (dev_addr<<1)|I2C_WRITE;
	I2C_Busy_Wait();
}


/**
 * @brief		Send the given data on the I2C bus (for the Repeat_write type
 * 				transmission)
 * @param[in]	data -> data to send on the I2C bus
 * @return	none
 */
void I2C_Repeat_Write_Byte(uint8_t data){
	// Send the data
	I2C1->D = data;
	I2C_Busy_Wait();
}

/**
 * @brief		Writes the given data on the I2C bus for the specified device
 * 				ID and address location
 * @param[in]	dev_addr -> Device address to which we should write the data
 * 				data_addr -> Address on the device to which we should write the
 * 							 given data
 * 				data -> data to send on the I2C bus to the device
 * @return	none
 */
void I2C_Write_Byte(uint8_t dev_addr, uint8_t data_addr, uint8_t data){
	I2C_Start_Tx();
	// Send the device ID
	I2C1->D = (dev_addr<<1) | I2C_WRITE;
	I2C_Busy_Wait();

	// Send the data_addr
	I2C1->D = data_addr;
	I2C_Busy_Wait();

	// Send the data
	I2C1->D = data;
	I2C_Busy_Wait();

	I2C_Stop();
}

/**
 * @brief		Reads the data from the specified address location from the
 * 				given device ID on the I2C bus
 * @param[in]	dev_addr -> Device address from which we should get the data from
 * 				data_addr -> Address on the device from which we should get the
 * 							 data from
 * @return		data recieved from the I2C device
 */
uint8_t I2C_Read_Byte(uint8_t dev_addr, uint8_t data_addr){
	uint8_t data=0;

	I2C_Start_Tx();
	// Send the device ID
	I2C1->D = (dev_addr<<1)|I2C_READ;
	I2C_Busy_Wait();

	// Send the data_addr
	I2C1->D = data_addr;
	I2C_Busy_Wait();

	I2C_Start_Rx(dev_addr);

	I2C1->C1 |= I2C_C1_TXAK_MASK; // Send NACK after recieving data
	I2C_Busy_Wait();

	I2C_Stop();

	data = I2C1->D;

	return data;

}
