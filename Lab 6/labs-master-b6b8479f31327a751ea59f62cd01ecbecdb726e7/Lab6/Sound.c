// Sound.c
// This module contains the SysTick ISR that plays sound
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 8/25/2014 
// Last Modified: 3/6/2015 
// Section 1-2pm     TA: Wooseok Lee
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data
#include <stdint.h>
#include "dac.h"
#include "tm4c123gh6pm.h"

extern int array_index;
extern int array[32];

// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Called once, with sound initially off
// Input: interrupt period
//           Units to be determined by YOU
//           Maximum to be determined by YOU
//           Minimum to be determined by YOU
// Output: none

	const uint32_t period[4] = {
		0x00FFFFFF,4780,4259,3794}; // period[0] is called when input=0, dummy value
	const uint8_t wave[32] = {
		8,10,11,12,13,14,14,15,15,15,14,14,13,12,11,10,8,7,5,4,2,1,1,0,0,0,1,1,2,4,5,7};

		
void Sound_Init(void){
	DAC_Init();
	void SysTick_Init(void);{
	NVIC_ST_CTRL_R = 0;// disable SysTick during setup
  NVIC_ST_RELOAD_R = 3794;//default reload value = period for note E
	NVIC_ST_CURRENT_R = 0;// clear current by writing to it
	NVIC_ST_CTRL_R = 0x00000007;// enable SysTick with core clock and interrupts
	}
		
	array_index = 0;
	int array_temp[32] = {8, 10, 11, 12, 13, 14, 14, 15, 15, 15, 14, 14, 13, 12, 11, 10, 8, 7, 5, 4, 2, 1, 1, 0, 0, 0, 1, 1, 2, 4, 5, 7};
	memcpy(array, array_temp, sizeof(array));
	DAC_Init();
	NVIC_ST_CTRL_R += 0x02;
}


// **************Sound_Play*********************
// Start sound output, and set Systick interrupt period 
// Input: interrupt period
//           Units to be determined by YOU
//           Maximum to be determined by YOU
//           Minimum to be determined by YOU
//         input of zero disable sound output
// Output: none
void Sound_Play(uint32_t note){
	uint32_t reloadvalue;
	reloadvalue = period[note];
	NVIC_ST_RELOAD_R = reloadvalue;
	
	 NVIC_ST_RELOAD_R = period;
}
