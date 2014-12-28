#ifndef producerConsumer_H
#define producerConsumer_H
#include "semaphore.h"
#include "Mutex.h"
#define   maxItem   3

extern unsigned char itemBuffer[maxItem];
extern int number;
extern Mutex itemMutex;
extern Semaphore emptyCount;
extern Semaphore filledCount;

void init();
void initToYieldList(int *yieldList, int maxYield);
void addItemToBuffer();
unsigned char retrieveItemFromBuffer();
void producer();
void consumer();

#endif // producerConsumer_H
