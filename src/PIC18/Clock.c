#include "Clock.h"
#include "Interrupt.h"
#include "Preemptive.h"
#include "Type.h"
#include "../18c.h"

#if !(defined(__XC) || defined(__18CXX))
  #include "timers.h"
#else
  #include <timers.h>
#endif // __18CXX

volatile unsigned long clock;
uint8 workingReg, bankSelectReg, statusReg, TOSHi, TOSLow, stkPTRH, stkPTRL;
uint16 task, stackPointer;

#pragma code high_vector=0x08
void highPriorityIsr(void){
    _asm
        goto timer0Isr
    _endasm
}
#pragma code

#pragma interruptlow timer0Isr save=FSR2L//why low? To store status/WREG/BSR, otherwise it store to shadow register(shadow reg only has one and may replacing by next interrupt)
void timer0Isr(void) {
  TCB *newTCB;
  TOSHi = TOSH;
  TOSLow = TOSL;
  clock++;
  clearTimer0Overflowed();
  // Get the highest priority task from the priority linked list
  // Insert the runningTCB into priority linked list
  // Restore all data in high priority task to
            // - TOS
            // - Stack Pointer
  // return from interrupt
  
  task = ((uint16)TOSHi)<<8 |TOSLow;
  runningTCB->task = task;
  stkPTRH = FSR1H;
  stkPTRL = FSR1L;
  stackPointer = (uint16)stkPTRH<<8|stkPTRL;
  runningTCB->stackPointer = stackPointer;
  newTCB = removeFromHeadPriorityLinkedList(&readyQueue);
  addTCB(&readyQueue, runningTCB);
  runningTCB = newTCB;

  TOSLow = runningTCB->task;
  TOSHi = (runningTCB->task)>>8;

  _asm
          movff TOSHi,WREG
          movwf TOSH,ACCESS
          movff TOSLow,WREG
          movwf TOSL,ACCESS
  _endasm
  stackPointer = runningTCB->stackPointer;
  FSR1H = stackPointer>>8;
  FSR1L = stackPointer;
}

void initClock(void) {
  clock = 0;
  enableGlobalInterrupt();
  OpenTimer0( TIMER_INT_ON &
              T0_8BIT &
              T0_SOURCE_INT &
              T0_PS_1_8);
}

/**
 * Return the micro-controller's clock since power-up.
 * 1 clock means 1.024 msec.
 */
unsigned long getCLOCK(void) {
  /*if(hasTimer0Overflowed()) {
    clearTimer0Overflowed();
    clock++;
  }*/
  return clock;
}

/////////////////////////////////////////
// These functions are for internal use
/////////////////////////////////////////
char hasTimer0Overflowed(void) {
  return INTCONbits.TMR0IF;
}

void clearTimer0Overflowed(void) {
  INTCONbits.TMR0IF = 0;
}


