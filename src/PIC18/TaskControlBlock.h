#ifndef _TASK_CONTROL_BLOCK_H_
#define _TASK_CONTROL_BLOCK_H_

typedef int             int16;
typedef long            int32;
typedef char            int8;
typedef unsigned int    uint16;
typedef unsigned long   uint32;
typedef unsigned char   uint8;

typedef struct TCB TCB;
struct TCB{
	TCB* next;
	uint8 priority;
	int dataStack;
	char status;
    uint16 stackPointer;
    int16 framePointer;
    char bsr;
    char Wreg;
    void (*task)(void); //Pointer to address//TOS
};

int compareTCBPriority(void *elementOfInterest, void *elementInList);

#endif // _TASK_CONTROL_BLOCK_H_