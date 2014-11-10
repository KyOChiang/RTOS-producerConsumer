#include "Clock.h"
#include "Interrupt.h"
#include "../18c.h"
#include "TaskControlBlock.h"
#include "PriorityLinkedList.h"

volatile unsigned long clock;
char workingReg, bankSelectReg, statusReg, TOSHi, TOSLo;

void interrupt timer0Isr() {
  #asm
    movwf _workingReg
    movff  STATUS, _statusReg
    movff  BSR, _bankSelectReg

//    movff TOSH, _TOSHi
//    movff TOSL, _TOSLo
  #endasm
  // save all above in asm into running TCB
  // Get the highest priority task from the priority linked list
  // Insert the runningTCB into priority linked list
  // Restore all data in high priority task to
            // - TOS
            // - BSR
            // - STATUS
            // - WREG
  // return from interrupt
  clock++;
  clearTimer0Overflowed();
}

void initClock() {
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
unsigned long getCLOCK() {
  /*if(hasTimer0Overflowed()) {
    clearTimer0Overflowed();
    clock++;
  }*/
  return clock;
}

/////////////////////////////////////////
// These functions are for internal use
/////////////////////////////////////////
char hasTimer0Overflowed() {
  return INTCONbits.TMR0IF;
}

void clearTimer0Overflowed() {
  INTCONbits.TMR0IF = 0;
}
