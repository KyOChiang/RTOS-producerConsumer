#include "Tasking.h"
#include "TaskControlBlock.h"
#include "Preemptive.h"
#include "PriorityLinkedList.h"
#include <stdio.h>
#include "producerConsumer.h"
#include "semaphore.h"
#include "Mutex.h"

#define   yieldOn(lineNumber, x) if((yieldAt[yieldIndex] == x) && (yieldIndex < totalYield)){yieldIndex++; yield(lineNumber);} else;
#define   maxItem   3

unsigned char itemBuffer[maxItem];
int number; // Index for itemBuffer

Mutex itemMutex;
Semaphore emptyCount;
Semaphore filledCount;

int yieldIndex;
int totalYield;
int *yieldAt;

void init(){
  number = 0;
  itemBuffer[0] = 0;
  itemBuffer[1] = 0;
  itemBuffer[2] = 0;
  
  initSemaphore(&emptyCount,3);
  initSemaphore(&filledCount,3);
  filledCount.count = 0;
  
  initMutex(&itemMutex);
}

void initToYieldList(int *yieldList, int maxYield){
  yieldIndex = 0;
  totalYield = maxYield;
  yieldAt = yieldList;
}

// Assume 0 to indicate there no data inside buffer
void addItemToBuffer(){
  if(number < maxItem){
    itemBuffer[number] = (rand() % 255) + 1;
    number+=1;
  }
  else // only come here for testing purpose
    printf("Buffer full\n");
}

unsigned char retrieveItemFromBuffer(){
  unsigned char retrieveItem;
  if(number == maxItem)
    number -=1;
  if(!(number<0)){
    retrieveItem = itemBuffer[number];
    itemBuffer[number] = 0;
    number-=1;
  }else //  only come here for testing purpose
    printf("No more data in buffer\n");
  return retrieveItem;
}

void producer(){
  startTasking(runningTCB->task);
  
  while(1){
    downSemaphore(&emptyCount);
    yieldOn(runningTCB->task, 1);
    
    acquireMutex(&itemMutex);
    yieldOn(runningTCB->task, 3);
    
    addItemToBuffer();
    yieldOn(runningTCB->task, 5);
    
    releaseMutex(&itemMutex);
    yieldOn(runningTCB->task, 7);
  
    upSemaphore(&filledCount);
    yieldOn(runningTCB->task, 9);
  }
  
  endTasking();
}

void consumer(){
  unsigned char retrieveItem;
  startTasking(runningTCB->task);
  
  while(1){
    downSemaphore(&filledCount);
    yieldOn(runningTCB->task, 2);
    
    acquireMutex(&itemMutex);
    yieldOn(runningTCB->task, 4);
    
    retrieveItem = retrieveItemFromBuffer();
    yieldOn(runningTCB->task, 6);
    
    releaseMutex(&itemMutex);
    yieldOn(runningTCB->task, 8);
    
    upSemaphore(&emptyCount);
    yieldOn(runningTCB->task, 10);
  }
  
  endTasking();
}