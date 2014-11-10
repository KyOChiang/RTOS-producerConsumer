/* File:   Blinky.c
 * Author: Chiang Choon Yong
 * Created on September 29, 2014, 11:19 AM*/

#include <stdio.h>
#include <stdlib.h>
#include "../18c.h"

#if !(defined(__XC) || defined(__18CXX))
  #include <usart.h>
#endif // __18CXX

void makeDelay(int loop) {
  unsigned long i;
  for(i = 0; i < loop; i++);
}

void configureLED(void) {
  TRISCbits.TRISC0 = 0;
}

void onLED(void) {
  PORTCbits.RC0 = 1;
}

void offLED(void) {
  PORTCbits.RC0 = 0;
}

