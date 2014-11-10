#ifndef _TASK_CONTROL_BLOCK_H_
#define _TASK_CONTROL_BLOCK_H_

typedef struct TCB TCB;
struct TCB{
	TCB* next;
	char priority;
	int dataStack;
	char status;
        char bsr;
        char Wreg;
        int (*task)(void); //Pointer to address//TOS
};

int compareTCBPriority(void *elementOfInterest, void *elementInList);

#endif // _TASK_CONTROL_BLOCK_H_