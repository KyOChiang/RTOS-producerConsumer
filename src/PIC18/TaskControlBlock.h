#ifndef _TASK_CONTROL_BLOCK_H_
#define _TASK_CONTROL_BLOCK_H_
#include "Type.h"

typedef struct TCB TCB;
struct TCB{
    TCB* next;
    uint8 priority;
    uint8 taskID;
    uint16 task;
    uint16 stackPointer;
    uint16 framePointer;
    //int dataStack;
    //char status;
    //char bsr;
    //char Wreg;
    //void (*task)(void); //Pointer to address//TOS
};

int compareTCBPriority(void *elementOfInterest, void *elementInList);

#endif // _TASK_CONTROL_BLOCK_H_