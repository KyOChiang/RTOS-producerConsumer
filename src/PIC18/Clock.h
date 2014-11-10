#ifndef Clock_H
#define Clock_H

#define TIMER_INT_OFF  0b01111111  //Disable TIMER Interrupt
#define T0_8BIT        0b11111111  //Timer0 is configured as an 8-bit timer/counter
#define T0_SOURCE_INT  0b11011111  //Internal instruction cycle clock (CLKO) acts as source of clock
#define T0_PS_1_8      0b11110010  //1:8 Prescale value

extern volatile unsigned long clock;

void initClock();
unsigned long getCLOCK();
char hasTimer0Overflowed();
void clearTimer0Overflowed();

#endif // Clock_H
