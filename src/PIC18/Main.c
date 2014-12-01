/* File:   Main.c
 * Author: Chiang Choon Yong
 * Created on September 29, 2014, 11:19 AM*/

#include "includePIC18.h"

char add(char a, char b){
    int result;
    result = a+b;
    return result;
}

void main(void) {
  initPreemptiveMultitasking();
  initClock();
  while(1);
}

/*
void closeModule(){
    CloseUSART();
    CloseSPI();
}
void main(void) {
  
  LoopbackData loopbackData;
  Led2Data led2Data;
  _7SEG _7SegData;

  add(5,2);
  setFreq8MHz();
  configureUsartTo8Bits9600Baud();
  configureLED();

  initClock();
  initUsartLoopback(&loopbackData);
  initTasking(&led2Data);
  init7Segment(&_7SegData);

  while(1) {
    usartLoopbackSM(&loopbackData);
    led2SM(&led2Data);
    _7SegmentSM(&_7SegData);
  }
  closeModule();
}*/


/* Test to blink LED.
  configureLED();
  while(1) {
      onLED();
      shortDelay();
      offLED();
      shortDelay();
  }
*/

/*Using SWITCH CASE statement
  LEDData ledData;
  initLed(&ledData);
  ledSM(&ledData);*/