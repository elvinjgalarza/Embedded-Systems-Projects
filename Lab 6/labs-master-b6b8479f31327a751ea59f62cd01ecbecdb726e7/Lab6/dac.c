// dac.c
// This software configures DAC output
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 8/25/2014 
// Last Modified: 3/6/2015 
// Section 1-2pm     TA: Wooseok Lee
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

#include <stdint.h>
#include "tm4c123gh6pm.h"
// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data

// **************DAC_Init*********************
// Initialize 6-bit DAC, called once 
// Input: none
// Output: none
void DAC_Init(void){
<<<<<<< .mine
		SYSCTL_RCGCGPIO_R |= 0x10; //activate clock for Port E
	while((SYSCTL_PRGPIO_R&0x01) == 0){};
		GPIO_PORTE_AMSEL_R &= ~0x0F; //no analog
		GPIO_PORTE_DIR_R |= 0x0F;// make PE0-3 output
		GPIO_PORTE_AFSEL_R &= ~0x0F;// disable alt funct on PE0-3
		GPIO_PORTE_DEN_R |= 0x0F; // enable digital I/O on PE0-3
		GPIO_PORTE_DR8R_R |= 0x0F;
||||||| .r21145
=======
	volatile uint32_t delay;
  SYSCTL_RCGCGPIO_R |= 0x00000032;  
  delay = SYSCTL_RCGCGPIO_R; 
	// DAC Outputs	
  GPIO_PORTE_DIR_R |= 0x3F;          // Output = 1 Input = 0
	GPIO_PORTE_DR8R_R |= 0x3F; 
  GPIO_PORTE_AFSEL_R &= 0x00;               
  GPIO_PORTE_DEN_R |= 0x3F;
>>>>>>> .r23018
}

// **************DAC_Out*********************
// output to DAC
// Input: 6-bit data, 0 to 15 
// Output: none
void DAC_Out(uint32_t data){
<<<<<<< .mine
	GPIO_PORTE_DATA_R = data;//output voltage
||||||| .r21145
=======
	GPIO_PORTE_DATA_R = data;	
>>>>>>> .r23018
}
