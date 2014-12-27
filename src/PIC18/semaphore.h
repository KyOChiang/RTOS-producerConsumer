#ifndef semaphore_H
#define semaphore_H

#include "TaskControlBlock.h"
#include "PriorityLinkedList.h"

typedef struct Semaphore Semaphore;
struct Semaphore{
char count;
char maxCount;
PriorityLinkedList waitingQueue;
};

void initSemaphore(Semaphore *semaphore, int initCount);
void upSemaphore(Semaphore *semaphore);
void downSemaphore(Semaphore *semaphore);

#endif // semaphore_H
