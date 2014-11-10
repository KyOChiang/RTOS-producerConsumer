#include "Clock.h"
#include "Interrupt.h"
#include "../18c.h"
#include "TaskControlBlock.h"
#include "PriorityLinkedList.h"
#include <timers.h>

volatile unsigned long clock;
char workingReg, bankSelectReg, statusReg, TOSHi, TOSLo;
#pragma interrupt timer0Isr
#pragma code high_vector=0x08
void highPriorityIsr(void){
    _asm
        goto timer0Isr
    _endasm
}
#pragma code
/////////////////////////////////////////
// These functions are for internal use
/////////////////////////////////////////
char hasTimer0Overflowed(void) {
  return INTCONbits.TMR0IF;
}

void clearTimer0Overflowed(void) {
  INTCONbits.TMR0IF = 0;
}


void timer0Isr(void) {
    
  _asm
    movwf workingReg, ACCESS
    movff STATUS, statusReg
    movff BSR, bankSelectReg

//    movff TOSH, _TOSHi
//    movff TOSL, _TOSLo
  _endasm
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

