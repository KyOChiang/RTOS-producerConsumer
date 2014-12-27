#include "unity.h"
#include "Mutex.h"
#include "TaskControlBlock.h"
#include "PriorityLinkedList.h"
#include "Preemptive.h"

void setUp(void){}

void tearDown(void){}

void test_initMutex(void){
	TCB taskA = {0};
	Mutex mutex;
	runningTCB = &taskA;
	initMutex(&mutex);
	
	TEST_ASSERT_EQUAL(1,mutex.count);
	TEST_ASSERT_EQUAL_PTR(NULL,mutex.owner);
	TEST_ASSERT_EQUAL_PTR(NULL,mutex.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL,mutex.waitingQueue.tail);
}

void test_acquireMutex_taskA_should_acquire_mutex(void){
	TCB taskA = {0};
	Mutex mutex;
	runningTCB = &taskA;
	initMutex(&mutex);
	acquireMutex(&mutex);
	
	TEST_ASSERT_EQUAL(0,mutex.count);
	TEST_ASSERT_EQUAL_PTR(&taskA,mutex.owner);
	TEST_ASSERT_EQUAL_PTR(NULL,mutex.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL,mutex.waitingQueue.tail);
}

void test_acquireMutex_taskA_able_to_acquire_mutex_for_twice(void){
	TCB taskA = {0};
	Mutex mutex;
	runningTCB = &taskA;
	initMutex(&mutex);
	acquireMutex(&mutex);
	acquireMutex(&mutex);
	
	TEST_ASSERT_EQUAL(-1,mutex.count);
	TEST_ASSERT_EQUAL_PTR(&taskA,mutex.owner);
	TEST_ASSERT_EQUAL_PTR(NULL,mutex.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL,mutex.waitingQueue.tail);
}

void test_acquireMutex_taskB_failed_to_acquire_mutex_and_get_blocked_because_mutex_owned_by_taskA(void){
	TCB taskA = {0};
	TCB taskB = {0};
	Mutex mutex;
	runningTCB = &taskA;
	initMutex(&mutex);
	acquireMutex(&mutex);
	runningTCB = &taskB;
	acquireMutex(&mutex);
	
	TEST_ASSERT_EQUAL(0,mutex.count);
	TEST_ASSERT_EQUAL_PTR(&taskA,mutex.owner);
	TEST_ASSERT_EQUAL_PTR(&taskB,mutex.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(&taskB,mutex.waitingQueue.tail);
}

void test_acquireMutex_for_previous_case_taskA_acquire_mutex_again(void){
	TCB taskA = {0};
	TCB taskB = {0};
	Mutex mutex;
	runningTCB = &taskA;
	initMutex(&mutex);
	acquireMutex(&mutex);
	runningTCB = &taskB;
	acquireMutex(&mutex);
	runningTCB = &taskA;
	acquireMutex(&mutex);
	
	TEST_ASSERT_EQUAL(-1,mutex.count);
	TEST_ASSERT_EQUAL_PTR(&taskA,mutex.owner);
	TEST_ASSERT_EQUAL_PTR(&taskB,mutex.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(&taskB,mutex.waitingQueue.tail);
}

void test_releaseMutex_taskA_able_to_release_mutex(void){
	TCB taskA = {0};
	Mutex mutex;
	readyQueue.head = NULL;
	readyQueue.tail = NULL;
	runningTCB = &taskA;
	initMutex(&mutex);
	acquireMutex(&mutex);
	releaseMutex(&mutex);
	
	TEST_ASSERT_EQUAL(1,mutex.count);
	TEST_ASSERT_EQUAL_PTR(NULL,mutex.owner);
	TEST_ASSERT_EQUAL_PTR(NULL,mutex.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL,mutex.waitingQueue.tail);
}

void test_releaseMutex_taskA_acquired_mutex_for_twice_should_release_mutex_for_twice(void){
	TCB taskA = {0};
	Mutex mutex;
	readyQueue.head = NULL;
	readyQueue.tail = NULL;
	runningTCB = &taskA;
	initMutex(&mutex);
	acquireMutex(&mutex);
	acquireMutex(&mutex);
	releaseMutex(&mutex);
	releaseMutex(&mutex);
	
	TEST_ASSERT_EQUAL(1,mutex.count);
	TEST_ASSERT_EQUAL_PTR(NULL,mutex.owner);
	TEST_ASSERT_EQUAL_PTR(NULL,mutex.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL,mutex.waitingQueue.tail);
}

void test_releaseMutex_taskB_cannot_release_mutex_that_owned_by_taskA(void){
	TCB taskA = {0};
	TCB taskB = {0};
	Mutex mutex;
	readyQueue.head = NULL;
	readyQueue.tail = NULL;
	runningTCB = &taskA;
	initMutex(&mutex);
	acquireMutex(&mutex);
	runningTCB = &taskB;
	releaseMutex(&mutex);
	
	TEST_ASSERT_EQUAL(0,mutex.count);
	TEST_ASSERT_EQUAL_PTR(&taskA,mutex.owner);
	TEST_ASSERT_EQUAL_PTR(NULL,mutex.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL,mutex.waitingQueue.tail);
}

void test_releaseMutex_taskB_can_acquire_mutex_after_it_released_by_taskA(void){
	TCB taskA = {0};
	TCB taskB = {0};
	Mutex mutex;
	readyQueue.head = NULL;
	readyQueue.tail = NULL;
	runningTCB = &taskA;
	initMutex(&mutex);
	acquireMutex(&mutex);
	runningTCB = &taskB;
	acquireMutex(&mutex);
	runningTCB = &taskA;
	releaseMutex(&mutex);
	
	TEST_ASSERT_EQUAL(0,mutex.count);
	TEST_ASSERT_EQUAL_PTR(&taskB,mutex.owner);
	TEST_ASSERT_EQUAL_PTR(NULL,mutex.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL,mutex.waitingQueue.tail);
	TEST_ASSERT_EQUAL_PTR(&taskB,readyQueue.head);
	TEST_ASSERT_EQUAL_PTR(&taskB,readyQueue.tail);
}

void test_releaseMutex_with_3_task(void){
	//Task A acquire first, follow by Task B and Task C but fail and get block
	//When Task A release, only task B can get mutex, task C must waiting task b to release
	TCB taskA = {0};
	TCB taskB = {0};
	TCB taskC = {0};
	Mutex mutex;
	//Clear readyQueue because it global and might be used by other test before
	readyQueue.head = NULL;
	readyQueue.tail = NULL;
	runningTCB = &taskA;
	initMutex(&mutex);
	acquireMutex(&mutex);	//taskA able acquire mutex
	runningTCB = &taskB;
	acquireMutex(&mutex);	//taskB unable acquire mutex/ get block
	
	TEST_ASSERT_EQUAL(0,mutex.count);
	TEST_ASSERT_EQUAL_PTR(&taskA,mutex.owner);
	TEST_ASSERT_EQUAL_PTR(&taskB,mutex.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(&taskB,mutex.waitingQueue.tail);
	
	runningTCB = &taskC;
	acquireMutex(&mutex);	//taskC unable acquire mutex/ get block
	
	TEST_ASSERT_EQUAL(0,mutex.count);
	TEST_ASSERT_EQUAL_PTR(&taskA,mutex.owner);
	TEST_ASSERT_EQUAL_PTR(&taskB,mutex.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(&taskC,taskB.next);
	TEST_ASSERT_EQUAL_PTR(&taskC,mutex.waitingQueue.tail);
	TEST_ASSERT_EQUAL_PTR(NULL,taskC.next);
	runningTCB = &taskA;
	releaseMutex(&mutex);	//taskA release, taskB get mutex, taskC still in blocking
	
	TEST_ASSERT_EQUAL(0,mutex.count);
	TEST_ASSERT_EQUAL_PTR(&taskB,mutex.owner);
	TEST_ASSERT_EQUAL_PTR(&taskC,mutex.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(&taskC,mutex.waitingQueue.tail);
	TEST_ASSERT_EQUAL_PTR(NULL,taskC.next);
	TEST_ASSERT_EQUAL_PTR(&taskB,readyQueue.head);
	TEST_ASSERT_EQUAL_PTR(&taskB,readyQueue.tail);
	TEST_ASSERT_EQUAL_PTR(NULL,taskB.next);
	
	runningTCB = &taskB;
	releaseMutex(&mutex);
	TEST_ASSERT_EQUAL(0,mutex.count);
	TEST_ASSERT_EQUAL_PTR(&taskC,mutex.owner);
	TEST_ASSERT_EQUAL_PTR(NULL,mutex.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL,mutex.waitingQueue.tail);
	TEST_ASSERT_EQUAL_PTR(&taskB,readyQueue.head);
  TEST_ASSERT_EQUAL_PTR(&taskC,taskB.next);
	TEST_ASSERT_EQUAL_PTR(&taskC,readyQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL,taskC.next);
	
	runningTCB = &taskC;
	releaseMutex(&mutex);
	TEST_ASSERT_EQUAL(1,mutex.count);
	TEST_ASSERT_EQUAL_PTR(NULL,mutex.owner);
	TEST_ASSERT_EQUAL_PTR(NULL,mutex.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL,mutex.waitingQueue.tail);
	TEST_ASSERT_EQUAL_PTR(&taskB,readyQueue.head);
	TEST_ASSERT_EQUAL_PTR(&taskC,readyQueue.tail);
  TEST_ASSERT_EQUAL_PTR(&taskC,taskB.next);
  TEST_ASSERT_EQUAL_PTR(NULL,taskC.next);
}