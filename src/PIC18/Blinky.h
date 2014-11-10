/* 
 * File:   Blinky.h
 * Author: Chiang Choon Yong
 *
 * Created on September 29, 2014, 11:19 AM
 */

#ifndef Blinky_H
#define Blinky_H

#define PIN_INPUT 1
#define PIN_OUTPUT 0
#define PIN_LOW 0
#define PIN_HIGH 1

void makeDelay(int loop);
void configureLED(void);
void onLED(void);
void offLED(void);

#endif // Blinky_H

