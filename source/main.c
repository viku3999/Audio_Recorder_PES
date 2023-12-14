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
 * @file    main.c
 * @brief   Implementation of the audio recorder and playback device
 * @author  Vishnu Kumar Thoodur Venkatachalapathy
 * @date    Dec 12, 2023
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "pin_mux.h"
//#include "test_sine.h"

#include <stdio.h>
//#include "DAC.h"
//#include "Waveforms.h"
//#include "DMA.h"
#include "TPM.h"
//#include "SysTick.h"
#include "I2C_KL25Z.h"
#include "MCP4725.h"
#include "ADC.h"
#include "RGB_LED.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define NUM_IP_SAMPLES 6615

#define MOD_VAL_T2_NOTE_A 426
#define MOD_VAL_T2_NOTE_B 380
#define MOD_VAL_T2_NOTE_C 717
#define MOD_VAL_T2_NOTE_D 639
#define MOD_VAL_T2_NOTE_E 569
#define MOD_VAL_T2_NOTE_F 537
#define MOD_VAL_T2_NOTE_G 478

#define MOD_VAL_T1_10Hz 39024

#define MOD_VAL_T0_IP_SAMPLING 1088  // Set timer 0 to 44.1KHz
#define MOD_VAL_T0_OP	24000	 // Set timer 0 to 2KHz so that the final o/p
								 // playback frequency shall be 1KHz



/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/**
 * @brief	Function to Sample Audio using a KY-037 microphone module and
 * 			playback the sampled audio
 * @return	none
 */
void Sample_Voice(){
	int time_ctr = 0, i=0;
	uint16_t Mic_Vals[NUM_IP_SAMPLES];

	// Set LED colour to RED to denote the microphone ON
    LED_CONTROL(1,0,0);
    PRINTF("\r\nStarting Voice Sample");

    // Set the TPM0 counter to generate a ITR at 44.1KHz and start TPM0 and 1
	Set_MOD_TPM0(MOD_VAL_T0_IP_SAMPLING);
	Start_TPM1();
	Start_TPM0();

	while(1){

		// Since we cannot set a timer for 1 second, we set a timer for 100ms
		// count it 10 times to get to 1 second
		if(TPM1_Flag){
			time_ctr++;
			if(time_ctr >= 10)
				break;
			TPM1_Flag = 0;
		}

		// store the ADC value (microphone data) into a buffer
		if(TPM0_Flag){
			Mic_Vals[i++] = Get_ADC_Val();

			// stop i/p gathering when the buffer is full
			if(i>=NUM_IP_SAMPLES){
				break;
			}
			TPM0_Flag = 0;
		}
	}

	// Stop the timers, setup TPM0 to generate a ITR at 2KHz and restart TPM0
	Stop_TPM0();
	Stop_TPM1();

    PRINTF("\r\nVoice Sampled\r\nStarting Playback");
	Set_MOD_TPM0(MOD_VAL_T0_OP);

	// Set LED colour to BLUE to denote the buzzer is active
    LED_CONTROL(0,0,1);

	Start_TPM0();
	i=0;
	while(1){
		if(TPM0_Flag){
			TPM0_Flag = 0;

			// set the DAC value to the Microphone data, wait till the TPM0 ISR
			// gets triggered, reset DAC value to 0, again wait till the TPM0 ISR
			// again gets triggered
			Set_DAC_Fast(Mic_Vals[i++]);
			while(TPM0_Flag == 0);
			Set_DAC_Fast(0x000);
			TPM0_Flag = 0;
			while(TPM0_Flag == 0);

			// exit sequence once we have played through the entire buffer
			if(i>=NUM_IP_SAMPLES){
				break;
			}
		}
	}

	// Set LED to GREEN colour to denote that the device is ready for new commands
	LED_CONTROL(0,1,0);
	PRINTF("\r\nVoice Playback done!");
}

/**
 * @brief	Function to generate a tone at frequency set in TPM2 for 1 second
 * @return	none
 */
void Generate_Tone(){

	int Time_ctr = 0;
	bool Tone_Count = true;

	// Set LED colour to BLUE to denote the buzzer is active
    LED_CONTROL(0,0,1);

    // Start TPM1 and 2 for audio playback
	Start_TPM1();
	Start_TPM2();
	while(1){

		// Since we cannot set a timer for 1 second, we set a timer for 100ms
		// count it 10 times to get to 1 second
		if(TPM1_Flag){
			Time_ctr++;
			if(Time_ctr >= 10)
				break;
			TPM1_Flag = 0;
		}

		// set the DAC value to the 0xFFF (4.9V), wait till the TPM0 ISR gets
		// triggered, reset DAC value to 0x000 (0V), again wait till the TPM0 ISR
		// again gets triggered

		if(TPM2_Flag){
			TPM2_Flag = 0;
			if(Tone_Count){
				Set_DAC_Fast(0xFFF);
				Tone_Count = false;
			}
			else{
				Set_DAC_Fast(0x000);
				Tone_Count = true;
			}
		}

	}

	// Set LED to GREEN colour to denote that the device is ready for new commands
    LED_CONTROL(0,1,0);

}

/**
 * @brief	Prints out all available commands
 * @return	none
 */
void Print_Menu(){
	PRINTF("\r\nA/a -> Play musical note 'A' at OCT 4 for 1sec");
	PRINTF("\r\nB/b -> Play musical note 'B' at OCT 4 for 1sec");
	PRINTF("\r\nC/c -> Play musical note 'C' at OCT 4 for 1sec");
	PRINTF("\r\nD/d -> Play musical note 'D' at OCT 4 for 1sec");
	PRINTF("\r\nE/e -> Play musical note 'E' at OCT 4 for 1sec");
	PRINTF("\r\nF/f -> Play musical note 'F' at OCT 4 for 1sec");
	PRINTF("\r\nG/g -> Play musical note 'G' at OCT 4 for 1sec");
	PRINTF("\r\nV/v -> Record voice and playback");
	PRINTF("\r\nEnter Selection: ");
}

/*
 * @brief Main function
 */
int main(void)
{
	/* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    TPM0_Init(MOD_VAL_T0_IP_SAMPLING);
	TPM1_Init(MOD_VAL_T1_10Hz);
    TPM2_Init(MOD_VAL_T2_NOTE_A);
    LED_SETUP();
    LED_CONTROL(0,1,0);
    PRINTF("\r\nPES Final Project\r\n");

    // Initializing required peripherals
    init_ADC0();
	Init_I2C();

	char User_Ip = '0';
    while (1)
    {
    	Print_Menu();
    	User_Ip = GETCHAR();
    	PUTCHAR(User_Ip);
    	switch(User_Ip){
    		case 'A':
    		case 'a':	PRINTF("\r\nPlaying Note 'A' for 1sec");
    					Set_MOD_TPM2(MOD_VAL_T2_NOTE_A);
    					Generate_Tone();
    					break;
    		case 'B':
    		case 'b':	PRINTF("\r\nPlaying Note 'B' for 1sec");
    					Set_MOD_TPM2(MOD_VAL_T2_NOTE_B);
    					Generate_Tone();
    					break;
    		case 'C':
    		case 'c':	PRINTF("\r\nPlaying Note 'C' for 1sec");
    					Set_MOD_TPM2(MOD_VAL_T2_NOTE_C);
    					Generate_Tone();
    					break;
    		case 'D':
    		case 'd':	PRINTF("\r\nPlaying Note 'D' for 1sec");
    					Set_MOD_TPM2(MOD_VAL_T2_NOTE_D);
    					Generate_Tone();
    					break;
    		case 'E':
    		case 'e':	PRINTF("\r\nPlaying Note 'E' for 1sec");
    					Set_MOD_TPM2(MOD_VAL_T2_NOTE_E);
    					Generate_Tone();
    					break;
    		case 'F':
    		case 'f':	PRINTF("\r\nPlaying Note 'F' for 1sec");
    					Set_MOD_TPM2(MOD_VAL_T2_NOTE_F);
    					Generate_Tone();
    					break;
    		case 'G':
    		case 'g':	PRINTF("\r\nPlaying Note 'G' for 1sec");
    					Set_MOD_TPM2(MOD_VAL_T2_NOTE_G);
    					Generate_Tone();
    					break;
    		case 'v':
    		case 'V':	Sample_Voice();
    					break;
    		default:	break;
    	}
    }
}
