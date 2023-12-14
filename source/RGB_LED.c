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
 * @file    RGB_LED.c
 * @brief   Required setup and interface functions to use the RGB LED on the
 * 			KL25Z dev board
 * @author  Vishnu Kumar Thoodur Venkatachalapathy
 * @date    Oct 2, 2023
 */

#include "board.h"
#include "MKL25Z4.h"
#include "pin_mux.h"
#include "RGB_LED.h"
#include "LOG.h"

/**
 * @brief     		Setups the onboard RGB LED for further use
 *
 * @return     		none
 */
void LED_SETUP(){
	// Enabling Ports B and D by sending clock signals to these ports
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;

	// Clearing previous PCR config (MUX config) for the respective LED pin
	PORTB -> PCR[RED_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB -> PCR[GREEN_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTD -> PCR[BLUE_LED_PIN] &= ~PORT_PCR_MUX_MASK;

	// Config all LED pins to be GPIO by setting 001 to the respective PCR addr
	PORTB -> PCR[RED_LED_PIN] |= PORT_PCR_MUX(1);
	PORTB -> PCR[GREEN_LED_PIN] |= PORT_PCR_MUX(1);
	PORTD -> PCR[BLUE_LED_PIN] |= PORT_PCR_MUX(1);

	// Setting LED ports to outputs
	RED_PORT->PDDR |= MASK(RED_LED_PIN);
	GREEN_PORT->PDDR |= MASK(GREEN_LED_PIN);
	BLUE_PORT->PDDR |= MASK(BLUE_LED_PIN);

	// Turning OFF all the LEDs by writing 1 to the ports
	RED_PORT->PCOR |= MASK(RED_LED_PIN);
	GREEN_PORT->PCOR |= MASK(GREEN_LED_PIN);
	BLUE_PORT->PCOR |= MASK(BLUE_LED_PIN);
}

/**
 * @brief     		Changes the Onboard RGB LED as per the given config
 *
 * @param[in]  r	Red LED state. Should be 1(ON) or 0(OFF)
 * @param[in]  g	Green LED state. Should be 1(ON) or 0(OFF)
 * @param[in]  b	Blue LED state. Should be 1(ON) or 0(OFF)
 *
 * @return     		none
 */
void LED_CONTROL(uint32_t r, uint32_t g, uint32_t b){

	/* Since the cathode of the LEDs are connected to the GPIO pins,
	 * The following logic shall apply:
	 * 	0 - LED On  (set the PCOR register for the respective LED pin)
	 * 	1 - LED Off	(set the PSOR register for the respective LED pin)
	 */

	if (r)
		RED_PORT->PCOR = MASK(RED_LED_PIN);
	else
		RED_PORT->PSOR = MASK(RED_LED_PIN);

	if (g)
		GREEN_PORT->PCOR = MASK(GREEN_LED_PIN);
	else
	    GREEN_PORT->PSOR = MASK(GREEN_LED_PIN);

	if (b)
	    BLUE_PORT->PCOR = MASK(BLUE_LED_PIN);
	else
	    BLUE_PORT->PSOR = MASK(BLUE_LED_PIN);

	if((r==1) && (g==0) && (b==0))
		LOG("\r\nCHANGE LED TO RED");
	else if ((r==0) && (g==1) && (b==0))
		LOG("\r\nCHANGE LED TO GREEN");
	else if ((r==0) && (g==0) && (b==1))
		LOG("\r\nCHANGE LED TO BLUE");
	else if ((r==1) && (g==1) && (b==0))
		LOG("\r\nCHANGE LED TO YELLOW");
	else if ((r==0) && (g==1) && (b==1))
		LOG("\r\nCHANGE LED TO CYAN");
	else if ((r==1) && (g==0) && (b==1))
		LOG("\r\nCHANGE LED TO MAGENTA");
	else if ((r==1) && (g==1) && (b==1))
		LOG("\r\nCHANGE LED TO WHITE");
	else{
	}
}
