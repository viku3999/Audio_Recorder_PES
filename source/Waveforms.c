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
 * @file    Waveforms.c
 * @brief   File containing waveform generation functions
 * @author  Vishnu Kumar Thoodur Venkatachalapathy
 * @date    Dec 1, 2023
 */

#include "Waveforms.h"
#include "fsl_debug_console.h"
#include "DMA.h"
#include "TPM.h"
#include "DAC.h"
#include "SysTick.h"
#include "ADC.h"
#include "autocorrelate.h"

uint16_t sq_buffer[BUFFER_SIZE], sine_buffer[BUFFER_SIZE], tri_buffer[BUFFER_SIZE];
int sq_buff_size, sine_buff_size, tri_buff_size;

#define SQ_wave_repeat 4
#define Sine_wave_repeat 6
#define Tri_wave_repeat 8

#define Sine_Step_Size 80
#define Tri_Step_Size 69

/**
 * @brief		Function to round off the given float value
 * @param[in]	x -> float value to round-off
 * @return		rounded-off value
 */
int round(float x){
	int y=x;
	if((x-y)>0.444444){
		return (y+1);
	}
	else
		return(y);
}

/**
 * @brief		Generates a square wave buffer using which the DAC can generate a
 * 				Square wave at the specified frequency and time
 * @param[in]	period -> time period in seconds for which the wave must
 * 				be geenrated
 * @return		none
 */
void SQ_Wave(float period){
	float period_samples_f = (period * num_samples);
	int period_samples_i = round(period_samples_f);
	int num_period_repeat_i = SQ_wave_repeat;
	sq_buff_size = num_period_repeat_i * period_samples_i;

	int x=0;
	for(int i=0; i<period_samples_i; i++){
		if(i<period_samples_i/2)
			x=0;
		else
			x=4079;

		sq_buffer[i] = x;
		sq_buffer[i+period_samples_i] = x;
		sq_buffer[i+(2*period_samples_i)] = x;
		sq_buffer[i+(3*period_samples_i)] = x;
	}

	PRINTF("\r\nGenerated %d samples at 400 Hz; computed period=%d samples", sq_buff_size, period_samples_i);
}

/**
 * @brief		Generates a sine wave buffer using which the DAC can generate a
 * 				sine wave at the specified frequency and time
 * @param[in]	period -> time period in seconds for which the wave must
 * 				be geenrated
 * @return		none
 */
void Sine_Wave(float period){
	float period_samples_f = (period * num_samples);
	int period_samples_i = round(period_samples_f);
	int num_period_repeat_i = Sine_wave_repeat;
	sine_buff_size = num_period_repeat_i * period_samples_i;

	int step_size_t = Sine_Step_Size;
	int x=0;

	for(int i=0; i<sine_buff_size; i++){
		sine_buffer[i] = fp_sin(x)+2047;
		x += step_size_t;
	}

	PRINTF("\r\nGenerated %d samples at 600 Hz; computed period=%d samples", sine_buff_size, period_samples_i);
}

/**
 * @brief		Generates a triangle wave buffer using which the DAC can generate a
 * 				triangle wave at the specified frequency and time
 * @param[in]	period -> time period in seconds for which the wave must
 * 				be geenrated
 * @return		none
 */
void Tri_Wave(float period){
	float period_samples_f = (period * num_samples);
	int period_samples_i = round(period_samples_f);
	int num_period_repeat_i = Tri_wave_repeat;
	tri_buff_size = num_period_repeat_i * period_samples_i;
	int step_size_t = Tri_Step_Size ;

	int x=2046;
	for(int i=0; i<tri_buff_size; i++){

		tri_buffer[i] = x;
		x += step_size_t;

		if(x>4095){
			x = 4095;
			step_size_t *= -1;
		}

		if(x<0){
			x=0;
			step_size_t *= -1;
		}
	}

	PRINTF("\r\nGenerated %d samples at 800 Hz; computed period=%d samples", tri_buff_size, period_samples_i);
}


/**
 * @brief	Function to start the waveform generation
 * @return	none
 */
void Start_Wave_Generation(){

	// Generate the buffers for Square, Sine, and Triangle waves
    SQ_Wave(0.00250);
    Sine_Wave(0.00167);
    Tri_Wave(0.00125);

    // Save the buffer information for the DAC to loop through
    SysTick_Set(sq_buffer, sq_buff_size,
    			sine_buffer, sine_buff_size,
				tri_buffer, tri_buff_size);

    // Start generating the waveform
	SysTick_Start();
}


/**
 * @brief	Function to start the input sampling
 * @return	none
 */
void Waveform_IP(){
	init_ADC0();

	// Initialize TPM1 at 48KHz
	TPM1_Init(1000);
	Start_TPM1();
}

/**
 * @brief	Function to analyse the generated waveform
 * @return	none
 */
void Waveform_Analyze(){

	int min = ADC_buff[0], max = ADC_buff[0], avg = ADC_buff[0];
	int16_t period = 0, freq = 0;

	// calculating the min, max and average values
	for(int i=1; i<1024; i++){

		if(ADC_buff[i] < min)
			min = ADC_buff[i];

		if(ADC_buff[i] > max)
			max = ADC_buff[i];

		avg += ADC_buff[i];
	}
	avg = avg/1024;

	// Getting the period from the auto-correlate function and
	period = autocorrelate_detect_period(ADC_buff, 1024, kAC_16bps_unsigned);
	freq = 48000/period;

	PRINTF("\r\nmin=%d max=%d avg=%d period=%d samples frequency=%d Hz", min, max, avg, period, freq);
}
