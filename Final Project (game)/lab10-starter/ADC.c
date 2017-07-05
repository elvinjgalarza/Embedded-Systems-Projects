// put implementations for functions, explain how it works
// put your names here, date
#include <stdint.h>
#include "tm4c123gh6pm.h"
// ADC initialization function 
// Input: none
// Output: none
	int delay;
void ADC_Init(void){ 
	SYSCTL_RCGCGPIO_R |= 0x00000010;					//activating clock for portE & F
	delay = SYSCTL_RCGCGPIO_R;
	delay = SYSCTL_RCGCGPIO_R;
	delay = SYSCTL_RCGCGPIO_R;
	GPIO_PORTE_DIR_R &= ~0x04;					//making PE2 input
	GPIO_PORTE_DEN_R &= ~0x04;
	GPIO_PORTE_AFSEL_R |= 0x04;
	SYSCTL_RCGCADC_R |= 0x01;				//activate ADC0
	delay = SYSCTL_RCGCADC_R;
	delay = SYSCTL_RCGCADC_R;
	delay = SYSCTL_RCGCADC_R;
	ADC0_PC_R = 0x01;									//configure for max of 125K
	ADC0_SSPRI_R = 0x0123;						//SEQUENCER 3 is highest priority
	ADC0_ACTSS_R &= ~0x0008;					//disable sample sequencer 3
	ADC0_EMUX_R &= ~0xF000;						//seq3 software trigger
	ADC0_SSMUX3_R = (ADC0_SSMUX3_R & 0xFFFFFFF0 ) + 1;    //channel Ain2 (PE2)
	ADC0_SSCTL3_R = 0x0006;           //NO TS0 D0, yes IE0 END0	
	ADC0_IM_R &= ~0x0008;							//disable SS3 interrupt
	ADC0_ACTSS_R |= 0x0008;						//ENABLE SEQ3
}
//------------ADC_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
	unsigned int result;
uint32_t ADC_In(void){  
	ADC0_PSSI_R = 0x0008;
	while((ADC0_RIS_R & 0x08) == 0){}
	result = ADC0_SSFIFO3_R & 0xFFF;
	ADC0_ISC_R = 0x0008;
  return result; 
}
