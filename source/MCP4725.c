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
 * @file    MCP4725.h
 * @brief   Header file for TPM module implementation
 * @author  Vishnu Kumar Thoodur Venkatachalapathy
 * @date    Dec 12, 2023
 */

#include "MCP4725.h"

#define DEVICE_ADDR (0x62)

#define HIGH_NIBBLE_FAST (0xF00)
#define LOW_NIBBLE_FAST (0x0FF)
#define HIGH_NIBBLE	(0xFF0)
#define LOW_NIBBLE	(0x00F)

#define HIGH_NIBBLE_SHIFT_FAST(x)	(x>>8)
#define LOW_NIBBLE_SHIFT_FAST(x)	(x>>0)
#define HIGH_NIBBLE_SHIFT(x)	(x>>4)
#define LOW_NIBBLE_SHIFT(x)		(x<<4)

#define CMD_DAC_FAST	(0x00)
#define CMD_DAC	(0b010)
#define CMD_DAC_EEPROM	(0b011)
#define CMD_SHIFT(x)	(x<<5)

#define PD_0	(0b00)
#define PD_1	(0b01)
#define PD_2	(0b10)
#define PD_3	(0b11)
#define PD_SHIFT_FAST(x)	(x<<4)
#define PD_SHIFT(x)	(x<<1)


/**
 * @brief	Function to Test the DAC module by sending 0xFFF as the DAC o/p value
 * @return	none
 */
void Test(){
	Init_I2C();
    I2C_Repeat_Write_Setup(DEVICE_ADDR);
    I2C_Repeat_Write_Byte(0x0F);
    I2C_Repeat_Write_Byte(0xFF);
    I2C_Repeat_Write_Byte(0x0F);
    I2C_Repeat_Write_Byte(0xFF);
    I2C_Stop();
}


/**
 * @brief		Sets only the DAC with the given value using the fast method
 * 				given in the module data sheet
 * @param[in]	Value -> value to be write into the DAC
 * @return		none
 */
void Set_DAC_Fast(uint16_t Value){
	uint8_t D0=0, D1=0;

	// Setting the D0 with the following config:
	//	C2, C1 = 0, Power Down mode = 0, Bit 11 to Bit 8 of the given DAC value
	// Setting D1 to store the first 8 bits of the given DAC value
	D0 = (CMD_DAC_FAST) | (PD_SHIFT_FAST(PD_0)) | (HIGH_NIBBLE_SHIFT_FAST(Value & HIGH_NIBBLE_FAST));
	D1 = (Value & LOW_NIBBLE_FAST);

	// Starting the I2C communication by sending the device address in write
	// mode, sending 4 bytes of data (D0, D1, D0, D1), and stopping communication
    I2C_Repeat_Write_Setup(DEVICE_ADDR);
    I2C_Repeat_Write_Byte(D0);
    I2C_Repeat_Write_Byte(D1);
    I2C_Repeat_Write_Byte(D0);
    I2C_Repeat_Write_Byte(D1);
    I2C_Stop();
}

void Set_DAC(uint16_t Value){	uint8_t D0=0, D1=0, D2=0;
	D0 = (CMD_SHIFT(CMD_DAC)) | PD_SHIFT(PD_0);
	D1 = HIGH_NIBBLE_SHIFT(Value & HIGH_NIBBLE);
	D2 = LOW_NIBBLE_SHIFT(Value & LOW_NIBBLE);

    I2C_Repeat_Write_Setup(DEVICE_ADDR);
    I2C_Repeat_Write_Byte(D0);
    I2C_Repeat_Write_Byte(D1);
    I2C_Repeat_Write_Byte(D2);
    I2C_Repeat_Write_Byte(D0);
    I2C_Repeat_Write_Byte(D1);
    I2C_Repeat_Write_Byte(D2);
    I2C_Stop();
}

void Set_DAC_EEPROM(uint16_t Value){
	uint8_t D0=0, D1=0, D2=0;
	D0 = (CMD_SHIFT(CMD_DAC_EEPROM)) | PD_SHIFT(PD_0);
	D1 = HIGH_NIBBLE_SHIFT(Value & HIGH_NIBBLE);
	D2 = LOW_NIBBLE_SHIFT(Value & LOW_NIBBLE);

    I2C_Repeat_Write_Setup(DEVICE_ADDR);
    I2C_Repeat_Write_Byte(D0);
    I2C_Repeat_Write_Byte(D1);
    I2C_Repeat_Write_Byte(D2);
    I2C_Repeat_Write_Byte(D0);
    I2C_Repeat_Write_Byte(D1);
    I2C_Repeat_Write_Byte(D2);
    I2C_Stop();
}
