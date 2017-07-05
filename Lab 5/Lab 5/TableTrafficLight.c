// ***** 0. Documentation Section *****
// TableTrafficLight.c for (Lab 10 edX), Lab 5 EE319K
// Runs on LM4F120/TM4C123
// Program written by: put your names here
// Date Created: 1/24/2015 
// Last Modified: 3/2/2016 
// Section 1-2pm     TA: Wooseok Lee
// Lab number: 5
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********
// east/west red light connected to PB5
// east/west yellow light connected to PB4
// east/west green light connected to PB3
// north/south facing red light connected to PB2
// north/south facing yellow light connected to PB1
// north/south facing green light connected to PB0
// pedestrian detector connected to PE2 (1=pedestrian present)
// north/south car detector connected to PE1 (1=car present)
// east/west car detector connected to PE0 (1=car present)
// "walk" light connected to PF3 (built-in green LED)
// "don't walk" light connected to PF1 (built-in red LED)

// ***** 1. Pre-processor Directives Section *****
#include <stdint.h>
#include "TExaS.h"
#include "tm4c123gh6pm.h"
#include "SysTick.h"
#define SENSORS  (*((volatile unsigned long *)0x400243FC)) // PORTE DATA (All Sensors)
#define TraLIGHT (*((volatile unsigned long *)0x400053FC)) // PORTB DATA (Traffic Lights)
#define PedLIGHT  (*((volatile unsigned long *)0x400253FC)) // PORTF DATA (Pedestrian Lights)

// ***** 2. Global Declarations Section *****
struct State {
	unsigned long OutTraffic;
	unsigned long OutPedestrian;
	unsigned long Time;
	unsigned long Next[8];
						 };
typedef const struct State STyp;
#define goN			0
#define waitN		1
#define goE			2
#define waitE		3
#define	walk		4
#define walk1		5
#define walk2		6
#define walk3		7
#define walk4		8
#define walk5		9
	
STyp FSM[10]={
 {0x21,0x02,200,{goN,goN,waitN,waitN,waitN,waitN,waitN,waitN}}, 		//goN
 {0x22,0x02,100,{goE,goE,goE,goE,walk,walk,walk,walk}},							//waitN
 {0x0C,0x02,200,{goE,waitE,goE,waitE,waitE,waitE,waitE,waitE}},			//goE
 {0x14,0x02,100,{goN,goN,goN,goN,walk,walk,walk,walk}},							//waitE
 {0x24,0x08,300,{walk,walk1,walk1,walk1,walk,walk,walk,walk}},			//walk
 {0x24,0x00,50,{walk2,walk2,walk2,walk2,walk2,walk2,walk2,walk2}},	//walk1
 {0x24,0x02,50,{walk3,walk3,walk3,walk3,walk3,walk3,walk3,walk3}},	//walk2
 {0x24,0x00,50,{walk4,walk4,walk4,walk4,walk4,walk4,walk4,walk4}},	//walk3
 {0x24,0x02,50,{walk5,walk5,walk5,walk5,walk5,walk5,walk5,walk5}},	//walk4
 {0x24,0x00,50,{goN,goN,goE,goN,goN,goN,goE,goN}}										//walk5
 
 };
// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

// ***** 3. Subroutines Section *****
unsigned long delay;
unsigned long Input;
unsigned long S = goN;
						 
int main(void){ 
  TExaS_Init(SW_PIN_PE210, LED_PIN_PB543210); // activate grader and set system clock to 80 MHz
  
	SYSCTL_RCGC2_R |= 0x32; 						// enables clocks for Pins B,E,F
	delay = SYSCTL_RCGC2_R;
  GPIO_PORTE_DEN_R |= 0x07;					  // PE2-0 virtual pins on (high = 1)
	GPIO_PORTE_DIR_R |= 0xF8;						// PE2-0 are INPUT
	GPIO_PORTE_AFSEL_R &= 0xF8;					// PE2-0 alternative functions are off
	
	GPIO_PORTB_DEN_R |= 0x3F;						// PB5-0 virtual pins on 
	GPIO_PORTB_DIR_R |= 0x3F;						// PB5-0 are OUTPUT
	GPIO_PORTB_AFSEL_R &= 0xC0;					// PB5-0 alternative functions are off
	
  EnableInterrupts();
  while(1){
    TraLIGHT = FSM[S].OutTraffic;			// sets up traffic lights
		PedLIGHT = FSM[S].OutPedestrian;	// sets up pedestrian lights
		Input = SENSORS;									// reads sensors
		SysTick_Wait10ms(FSM[S].Time);
		
  }
}

