// Lab6.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// MOOC lab 13 or EE319K lab6 starter
// Program written by: put your names here
// Date Created: 1/24/2015 
// Last Modified: 3/6/2015 
// Section 1-2pm     TA: Wooseok Lee
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********


#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "dac.h"
#include "Sound.h"
#include "SysTick.h"
#include "Piano.h"
#include "TExaS.h"
<<<<<<< .mine
#include "dac.h"
||||||| .r21145
=======
#include "Timer0A.h"
>>>>>>> .r23018


// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
<<<<<<< .mine
extern const uint8_t wave[32];
extern const uint32_t period[4];
||||||| .r21145
=======
// A-G => A-G5; 1-5 => A#-G#5; c-g => C-G4; 6-0 => A#-G#4 
char notes_array[32] = {'c', 'g', 'f', 'e', 'd', 'C', 'g', 'f', 'e', 'd', 'C', 'g', 'f', 'e', 'f', 'd', 'c', 'g', 'f', 'e', 'd', 'C', 'g', 'f', 'e', 'd', 'C', 'g', 'f', 'e', 'f', 'd'}; 
int notes_count = 0;
int time_array[32] = {6, 3, 1, 1, 1, 6, 3, 1, 1, 1, 6, 3, 1, 1, 1, 12, 6, 3, 1, 1, 1, 6, 3, 1, 1, 1, 6, 3, 1, 1, 1, 6};
int time_count = 0;
int playing_song = 0;
int tempo = 400000000/16;
>>>>>>> .r23018

<<<<<<< .mine
int main(void){      
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
||||||| .r21145

int main(void){      
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
=======
void SysTick_Handler(void){
	volatile uint32_t delay;
  SYSCTL_RCGCGPIO_R |= 0x00000032;  
  delay = SYSCTL_RCGCGPIO_R; 
	GPIO_PORTF_DATA_R |= 0x04;
	// Find the correct point on the sine wave to output
	if(array_index > 31){
		array_index = 0;
	}
  DAC_Out(array[array_index]);
	array_index++;
	GPIO_PORTF_DATA_R &= ~0x04;
}
void Time0_Handler(void){
	uint32_t data;
	char note;
	int counter;
	// Get note then increment
	if(notes_count < sizeof(notes_array)){
		note = notes_array[notes_count];
		notes_count++;
		counter = time_count;
		time_count++;
	}
	else{
		notes_count = 0;
		time_count = 0;
		counter = time_count;
		DisableInterrupts();
		playing_song = 0;
	}
	// Parse Notes
	switch(note){
		case 'a':
			data = 11344;
			break;
		case '6':
			data = 10706;
			break;
		case 'b':
			data = 10108;
			break;
		case 'c':
			data = 9540;
			break;
		case '7':
			data = 9003;
			break;
		case 'd':
			data = 8497;
			break;
		case '8':
			data = 8022;
			break;
		case 'e':
			data = 7572;
			break;
		case 'f':
			data = 7147;
			break;
		case '9':
			data = 6745;
			break;
		case 'g':
			data = 6366;
			break;
		case '0':
			data = 6013;
			break;
		case 'A':
			data = 5671;
			break;
		case '1':
			data = 5355;
			break;
		case 'B':
			data = 5053;
			break;
		case 'C':
			data = 4773;
			break;
		case '2':
			data = 4501;
			break;
		case 'D':
			data = 4251;
			break;
		case '3':
			data = 4010;
			break;
		case 'E':
			data = 3787;
			break;
		case 'F':
			data = 3573;
			break;
		case '4':
			data = 3372;
			break;
		case 'G':
			data = 3183;
			break;
		case '5':
			data = 3005;
			break;
		default:
			data = 4773;
			break;
	}
	TIMER0_TAILR_R = tempo * time_array[counter]; // Reset Timer0A
  Sound_Play(data);                
}
void Song(int tempo){
	// Timer 0 Init
	Timer0A_Init(&Time0_Handler, tempo);
}
int main(void){
	volatile uint32_t delay;
  SYSCTL_RCGCGPIO_R |= 0x00000032;  
  delay = SYSCTL_RCGCGPIO_R; 
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R = 0x1F;
	// Switch inputs
	GPIO_PORTF_DIR_R |= 0x06;          // Output = 1 Input = 0
	GPIO_PORTF_DIR_R &= ~0x11;
  GPIO_PORTF_DEN_R |= 0x17;	
	GPIO_PORTF_PUR_R |= 0x11;		
  GPIO_PORTF_AFSEL_R &= 0x00;               
	
  TExaS_Init(SW_PIN_PB3210,DAC_PIN_PE3210,ScopeOn);    // Actual PE is 5-0
>>>>>>> .r23018
  Piano_Init();
<<<<<<< .mine
  Sound_Init();// calls DAC_Init
		SYSCTL_RCGCGPIO_R |= 0x20; //activate clock for Port F
	while((SYSCTL_PRGPIO_R&0x01) == 0){};
		GPIO_PORTF_AMSEL_R &= ~0x06; //no analog
		GPIO_PORTF_DIR_R |= 0x06;// make PF1-2 output
		GPIO_PORTF_AFSEL_R &= ~0x06;// disable alt funct on PF1-2
		GPIO_PORTF_DEN_R |= 0x06; // enable digital I/O on PF1-2
  DisableInterrupts();
		
  while(1){      
	GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R^0x02;// heartbeat
		for (uint32_t delay = 1240000; delay > 0; delay--);
	uint32_t note = 0;
	note = Piano_In();// check piano inputs
	if (note == 0) {
		DisableInterrupts();
	}// no output if no buttons are pressed
	else {
		EnableInterrupts();
	  Sound_Play(note);
	}
  }
}	
	
  void SysTick_Handler(void) {
		static uint32_t i=0;// one time intialization
	GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R^0x04;// heartbeat
		uint32_t data;
		data = wave[i];//outputs voltages in a sine wave
		DAC_Out(data);
		i++;
		if (i>31){
			i = 0;
	}
||||||| .r21145
  Sound_Init(0);
  // other initialization
  EnableInterrupts();
  while(1){                
  }         
=======
	SysTick_Init();
	Sound_Init(0);
	EnableInterrupts();
  int heartbeat = 0;
	uint32_t data;	
  while(1){
		// Heartbeat
		if(heartbeat > 80000){
			GPIO_PORTF_DATA_R ^= 0x02;
			heartbeat = 0;
		}
		heartbeat++;
		//
 		data = Piano_In();
		if(playing_song == 0){
			if((data & 0x01) == 0x01){
				// Key 0 is pressed resulting in a C
				EnableInterrupts();
				data = 4773;
				Sound_Play(data);
			}
			else if ((data & 0x02) == 0x02){
				// Key 1 is pressed resulting in a D
				EnableInterrupts();		
				data = 4251;
				Sound_Play(data);
			}
			else if ((data & 0x04) == 0x04){
				// Key 2 is pressed resulting in a E
				EnableInterrupts();					
				data = 3787;
				Sound_Play(data);
			}
			else if ((data & 0x20) == 0x00){
				// Play button is pressed	
				playing_song = 1;
				EnableInterrupts();
				Song(tempo);
			}
			else{
				// No Key is pressed resulting in nothing
				DisableInterrupts();
			}
		}
		else{
			if ((data & 0x10) == 0x00){
				// Stop button is pressed				
				DisableInterrupts();
				playing_song = 0;
			}
		}
		
  }	
>>>>>>> .r23018
}



