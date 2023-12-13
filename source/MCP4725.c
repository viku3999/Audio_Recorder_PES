/*
 * MCP4725.c
 *
 *  Created on: Dec 13, 2023
 *      Author: vishn
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

void Test(){
	Init_I2C();
    I2C_Repeat_Write_Setup(DEVICE_ADDR);
    I2C_Repeat_Write_Byte(0x0F);
    I2C_Repeat_Write_Byte(0xFF);
    I2C_Repeat_Write_Byte(0x0F);
    I2C_Repeat_Write_Byte(0xFF);
    I2C_Stop();
}

void Set_DAC_Fast(uint16_t Value){
	uint8_t D0=0, D1=0;
	D0 = (CMD_DAC_FAST) | (PD_SHIFT_FAST(PD_0)) | (HIGH_NIBBLE_SHIFT_FAST(Value & HIGH_NIBBLE_FAST));
	D1 = (Value & LOW_NIBBLE_FAST);

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
