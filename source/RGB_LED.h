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
 * @file    RGB_LED.h
 * @brief   Required setup and interface functions prototypes to use the RGB
 * 			LED on the KL25Z dev board
 * @author  Vishnu Kumar Thoodur Venkatachalapathy
 * @date    Oct 2, 2023
 */

// Pin and port definitions for the onboard RGB LED
#define RED_LED_PIN		(18)
#define	GREEN_LED_PIN	(19)
#define	BLUE_LED_PIN	(1)
#define RED_PORT	PTB
#define GREEN_PORT	PTB
#define BLUE_PORT	PTD

#define MASK(x) (1UL << (x))

void LED_SETUP();

void LED_CONTROL(uint32_t r, uint32_t g, uint32_t b);
