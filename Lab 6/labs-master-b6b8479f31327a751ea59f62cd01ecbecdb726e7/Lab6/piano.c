// Piano.c
// This software configures the off-board piano keys
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
#include "tm4c123gh6pm.h"

// **************Piano_Init*********************
// Initialize piano key inputs, called once 
// Input: none 
// Output: none
void Piano_Init(void){
<<<<<<< .mine
	SYSCTL_RCGCGPIO_R |= 0x01; //activate clock for Port A
	while((SYSCTL_PRGPIO_R&0x01) == 0){};
		GPIO_PORTA_AMSEL_R &= ~0x3C; //no analog
		GPIO_PORTA_DIR_R &= ~0x3C;// make PA2-5 input
		GPIO_PORTA_AFSEL_R &= ~0x3C;// disable alt funct on PA2-5
		GPIO_PORTA_DEN_R |= 0x3C; // enable digital I/O on PA2-5
||||||| .r21145
=======
	volatile uint32_t delay;
  SYSCTL_RCGCGPIO_R |= 0x00000032;  
  delay = SYSCTL_RCGCGPIO_R; 
	// Switch inputs
	GPIO_PORTB_DIR_R &= ~0x0F;          // Output = 1 Input = 0
  GPIO_PORTB_AFSEL_R &= 0x00;               
  GPIO_PORTB_DEN_R |= 0x0F;
>>>>>>> .r23018
}

// **************Piano_In*********************
// Input from piano key inputs 
// Input: none 
// Output: 0 to 7 depending on keys
// 0x01 is just Key0, 0x02 is just Key1, 0x04 is just Key2
uint32_t Piano_In(void){
<<<<<<< .mine
  uint32_t input;
	input = GPIO_PORTA_DATA_R;// read switches
	return input;
||||||| .r21145
  return 0; // replace this line with actual code
=======
	uint32_t data = (GPIO_PORTB_DATA_R&0x07);
	data |= (((GPIO_PORTF_DATA_R&0x01)<<5)+(GPIO_PORTF_DATA_R&0x10)); // Get two switches input and mask/shift bits to proper places
  return data; // replace this line with actual code
>>>>>>> .r23018
}
