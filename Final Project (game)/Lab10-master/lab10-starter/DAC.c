// put implementations for functions, explain how it works
// put your names here, date
// put implementations for functions, explain how it works
// put your names here, date

#include <stdint.h>
#include "tm4c123gh6pm.h"


void DAC_Init(void){
		SYSCTL_RCGCGPIO_R |= 0x02; //activate clock for Port B
	while((SYSCTL_RCGCGPIO_R&0x02) == 0){};
		GPIO_PORTB_AMSEL_R &= ~0x0F; //no analog
		GPIO_PORTB_DIR_R |= 0x0F;// make PE0-3 output
		GPIO_PORTB_AFSEL_R &= ~0x0F;// disable alt funct on PE0-3
		GPIO_PORTB_DEN_R |= 0x0F; // enable digital I/O on PE0-3
		GPIO_PORTB_DR8R_R |= 0x0F;
}

// **************DAC_Out*********************
// output to DAC
// Input: 6-bit data, 0 to 15 
// Output: none
void DAC_Out(uint32_t data){
	GPIO_PORTB_DATA_R = data;				//output voltage

}
