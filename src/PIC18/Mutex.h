#ifndef Mutex_H
#define Mutex_H

#include "TaskControlBlock.h"
#include "PriorityLinkedList.h"
#include "Preemptive.h"
typedef struct Mutex Mutex;
struct Mutex{
char count;
TCB *owner;
PriorityLinkedList waitingQueue;
};

void initMutex(Mutex *mutex);
void acquireMutex(Mutex *mutex);
void releaseMutex(Mutex *mutex);
#endif // Mutex_H
