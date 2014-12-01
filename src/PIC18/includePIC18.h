/* 
 * File:   includePIC18.h
 * Author: Chiang Choon Yong
 *
 * Created on November 3, 2014, 3:37 PM
 */

#ifndef INCLUDEPIC18_H
#define	INCLUDEPIC18_H

//#include "LEDSM.h"

#include <stdio.h>
#include <stdlib.h>
#include "Blinky.h"
//#include "Loopback.h"
#include "Clock.h"
#include "Led2.h"
#include "SevenSeg.h"
#include "UsartLoopback.h"
#include "Tasking.h"
#include "Interrupt.h"
#include "PriorityLinkedList.h"
#include "TaskControlBlock.h"
#include "Preemptive.h"
#include "../18c.h"
#if !(defined(__XC) || defined(__18CXX))
  #include "usart.h"
  #include "spi.h"
  #include "timers.h"
#else
    #include <usart.h>
    #include <spi.h>
    #include <timers.h>
#endif // __18CXX

#pragma config OSC = INTIO67, PWRT = ON, WDT = OFF, LVP = OFF, DEBUG = ON

#define setFreq8MHz() (OSCCONbits.IRCF = 7)

#define configureUsartTo8Bits9600Baud()\
          OpenUSART(USART_TX_INT_OFF &\
                    USART_RX_INT_OFF &\
                    USART_ASYNCH_MODE &\
                    USART_EIGHT_BIT &\
                    USART_CONT_RX &\
                    USART_BRGH_HIGH, 51);

#endif	/* INCLUDEPIC18_H */

