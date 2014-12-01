#ifndef Mutex_H
#define Mutex_H

#include "TaskControlBlock.h"

typedef struct Mutex Mutex;
struct Mutex{
char count;
TCB *owner;
TCB *waitingQueue;
};

void initMutex(Mutex *mutex);
void acquireMutex(Mutex *mutex);
void releaseMutex(Mutex *mutex);
#endif // Mutex_H
