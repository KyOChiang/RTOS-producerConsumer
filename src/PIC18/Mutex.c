#include <stdio.h>
#include "Mutex.h"
#include "TaskControlBlock.h"
#include "PriorityLinkedList.h"
#include "Preemptive.h"

void initMutex(Mutex *mutex){
	mutex->count = 1;
	mutex->owner = NULL;
	mutex->waitingQueue.head = NULL;
	mutex->waitingQueue.tail = NULL;
}

void acquireMutex(Mutex *mutex){
	if(mutex->count == 1){
		mutex->count--;
		mutex->owner = runningTCB;
	}
	else{
		if(mutex->owner != runningTCB){
			addTCB(&(mutex->waitingQueue),runningTCB);}
		else
			mutex->count--; //has to release twice if same owner acquire for twice
	}
}

void releaseMutex(Mutex *mutex){
	if(mutex->owner != runningTCB){	// Not allow to release if owner is not mutex's owner, ignore
	}
	else{
		mutex->count++;
		if(mutex->count == 1){
		// check other task in waiting queue, let them acquire mutex
			mutex->owner = removeFromHeadPriorityLinkedList(&(mutex->waitingQueue));
			addTCB(&readyQueue,mutex->owner);
			if(mutex->owner != NULL) //new owner
				mutex->count--;
		}	
	}
}