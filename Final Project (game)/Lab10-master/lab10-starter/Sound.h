// Sound.h
// Runs on TM4C123 or LM4F120
// Prototypes for basic functions to play sounds from the
// original Space Invaders.
// Jonathan Valvano
// November 17, 2014


void Sound_Play(const uint8_t *pt, uint32_t count);

void Sound_Out(void);

void Sound_Init(void);
