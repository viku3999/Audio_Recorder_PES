/*
 * I2C_KL25Z.c
 *
 *  Created on: Dec 12, 2023
 *      Author: vishn
 */

#include "I2C_KL25Z.h"

#define I2C_WRITE (1<<0)
#define I2C_READ (0<<0)

void Init_I2C(){
	// Enable clk to I2C
	SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;

	//Enable clk to Port E for the I2C pins
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

	// I2C Config

	// Setting As master and I2C Baud rate to 100KHz. Mul -> 8, divider -> 0
	I2C1->F = (0x2 << I2C_F_MULT_SHIFT) | (0x00 << I2C_F_ICR_SHIFT);

	//Enable I2C module
	I2C1->C1 |= I2C_C1_IICEN_MASK | I2C_C1_IICIE_MASK;

	// Select high drive???
	I2C1->C2 |= I2C_C2_HDRS_MASK;
	//Init RAM variables for Tx data (IICEN = 1, IICIE = 1)

	// GPIO Config
	PORTE->PCR[0] |= PORT_PCR_MUX(6); // PE0 -> SDA
	PORTE->PCR[1] |= PORT_PCR_MUX(6); // PE1 -> SCL
}

void I2C_Start_Tx(){
	I2C1->C1 |= I2C_C1_TX_MASK; // Set Transmission Mode
	I2C1->C1 |= I2C_C1_MST_MASK;
}

void I2C_Start_Rx(uint8_t dev_addr){

	I2C1->C1 |= I2C_C1_RSTA_MASK; // Sending Re-Start command
	I2C1->D = (dev_addr<<1)|I2C_WRITE;
	I2C_Busy_Wait();

	I2C1->C1 &= ~I2C_C1_TX_MASK;
	I2C_Busy_Wait();
}

void I2C_Stop(){
	I2C1->C1 &= ~I2C_C1_MST_MASK;
}

void I2C_Busy(){

}

// TBD
void I2C_Busy_Wait(){
//	int lock_detect = 0;
//	while(((I2C1->S & I2C_S_IICIF_MASK)==0) & (lock_detect < 200)) {
//		lock_detect++;
//	}

//	if (lock_detect >= 200)
//		I2C_Busy();

	while(((I2C1->S & I2C_S_IICIF_MASK)==0) || ((I2C1->S & I2C_S_TCF_MASK) == 0));

	I2C1->S |= 1<<I2C_S_IICIF_SHIFT;
}

void I2C_Repeat_Write_Setup(uint8_t dev_addr){
	I2C_Start_Tx();
	I2C1->D = (dev_addr<<1)|I2C_READ;
	I2C_Busy_Wait();
}

void I2C_Repeat_Write_Byte(uint8_t data){
	I2C1->D = data;
	I2C_Busy_Wait();
}

void I2C_Write_Byte(uint8_t dev_addr, uint8_t data_addr, uint8_t data){
	I2C_Start_Tx();
	I2C1->D = dev_addr;
	I2C_Busy_Wait();

	I2C1->D = data_addr;
	I2C_Busy_Wait();

	I2C1->D = data;
	I2C_Busy_Wait();

	I2C_Stop();
}

uint8_t I2C_Read_Byte(uint8_t dev_addr, uint8_t data_addr){
	uint8_t data=0;

	I2C_Start_Tx();
	I2C1->D = (dev_addr<<1)|I2C_READ;
	I2C_Busy_Wait();

	I2C1->D = data_addr;
	I2C_Busy_Wait();

	I2C_Start_Rx(dev_addr);


	I2C1->C1 |= I2C_C1_TXAK_MASK; // Send NACK after recieving data
	I2C_Busy_Wait();

	I2C_Stop();

	data = I2C1->D;

	return data;

}
