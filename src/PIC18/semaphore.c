#include <stdio.h>
#include "semaphore.h"
#include "PriorityLinkedList.h"
#include "TaskControlBlock.h"
#include "Preemptive.h"

void initSemaphore(Semaphore *semaphore, int initCount){
	semaphore->maxCount = initCount;
  semaphore->count = initCount;
	semaphore->waitingQueue.head = NULL;
	semaphore->waitingQueue.tail = NULL;
}

void upSemaphore(Semaphore *semaphore){
// up
// semaphore++
// if > max, block the task itself
  TCB* taskWakedUp;
  if(semaphore->count<semaphore->maxCount){
    semaphore->count++;
    while((semaphore->waitingQueue).head != NULL){
      taskWakedUp = removeFromHeadPriorityLinkedList(&(semaphore->waitingQueue));
      addTCB(&readyQueue,taskWakedUp);
    }
  }
}

void downSemaphore(Semaphore *semaphore){
// down
// semaphore--
// if = 0, wake up/ release task in wating queue
  if(semaphore->count > 0)
    semaphore->count--;
  else if(semaphore->count == 0)
    addTCB(&(semaphore->waitingQueue),runningTCB);
  
}

// Initial value
// emptyCount = MAX
// fillCount = 0

/* Producer
 * down emptyCount emptyCount = 0, buffer full of data, producer should sleep
 * up fillCount fillCount = MAX, buffer full of data, wake up consumer
 *
 * Consumer
 * down fillCount fillCount = 0, buffer has no data, consumer go sleep
 * up emptyCount emptyCount = MAX, buffer has no data, producer wake up
 */
