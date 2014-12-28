#include "unity.h"
#include "semaphore.h"
#include "TaskControlBlock.h"
#include "PriorityLinkedList.h"
#include "Preemptive.h"

void setUp(void){}

void tearDown(void){}

void test_initSemaphore_should_assign_5_to_count_and_maxCount_and_clear_waitingQueue(void){
	Semaphore fillSemaphore;
  initSemaphore(&fillSemaphore,5);
  
  TEST_ASSERT_EQUAL(5,fillSemaphore.count);
  TEST_ASSERT_EQUAL(5,fillSemaphore.maxCount);
  TEST_ASSERT_EQUAL_PTR(NULL,fillSemaphore.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL,fillSemaphore.waitingQueue.tail);
}

void test_downSemaphore_given_sema_count_is_3_taskA_able_minus_count_by_1(void){
  Semaphore sema;
  TCB taskA = {0};
  runningTCB = &taskA;
  
  initSemaphore(&sema,3);
  downSemaphore(&sema);
  
  TEST_ASSERT_EQUAL(2,sema.count);
  TEST_ASSERT_EQUAL(3,sema.maxCount);
  TEST_ASSERT_EQUAL_PTR(NULL,sema.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL,sema.waitingQueue.tail);
}

void test_downSemaphore_given_sema_count_is_0_taskA_not_able_minus_count_by_1_and_get_blocked(void){
  Semaphore sema;
  TCB taskA = {0};
  runningTCB = &taskA;
  
  initSemaphore(&sema,3);
  sema.count = 0;
  downSemaphore(&sema);
  
  TEST_ASSERT_EQUAL(0,sema.count);
  TEST_ASSERT_EQUAL(3,sema.maxCount);
  TEST_ASSERT_EQUAL_PTR(&taskA,sema.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(&taskA,sema.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL,taskA.next);
}

void test_downSemaphore_given_sema_count_is_3_taskA_cannot_minus_count_after_3_times_and_put_inside_blocking(void){
  Semaphore sema;
  TCB taskA = {0};
  runningTCB = &taskA;
  
  initSemaphore(&sema,3);
  downSemaphore(&sema);
  
  TEST_ASSERT_EQUAL(2,sema.count);
  TEST_ASSERT_EQUAL(3,sema.maxCount);
  TEST_ASSERT_EQUAL_PTR(NULL,sema.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL,sema.waitingQueue.tail);
  
  downSemaphore(&sema);
  
  TEST_ASSERT_EQUAL(1,sema.count);
  TEST_ASSERT_EQUAL(3,sema.maxCount);
  TEST_ASSERT_EQUAL_PTR(NULL,sema.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL,sema.waitingQueue.tail);
  
  downSemaphore(&sema);
  
  TEST_ASSERT_EQUAL(0,sema.count);
  TEST_ASSERT_EQUAL(3,sema.maxCount);
  TEST_ASSERT_EQUAL_PTR(NULL,sema.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL,sema.waitingQueue.tail);
  
  downSemaphore(&sema);
  
  TEST_ASSERT_EQUAL(0,sema.count);
  TEST_ASSERT_EQUAL(3,sema.maxCount);
  TEST_ASSERT_EQUAL_PTR(&taskA,sema.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(&taskA,sema.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL,taskA.next);
}

void test_downSemaphore_given_sema_count_is_0_taskB_not_able_minus_count_by_1_and_get_blocked_after_taskA(void){
  Semaphore sema;
  TCB taskA = {0};
  TCB taskB = {0};
  runningTCB = &taskA;
  
  initSemaphore(&sema,3);
  sema.count = 0;
  downSemaphore(&sema);
  
  TEST_ASSERT_EQUAL(0,sema.count);
  TEST_ASSERT_EQUAL(3,sema.maxCount);
  TEST_ASSERT_EQUAL_PTR(&taskA,sema.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(&taskA,sema.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL,taskA.next);
  
  runningTCB = &taskB;
  downSemaphore(&sema);
  TEST_ASSERT_EQUAL(0,sema.count);
  TEST_ASSERT_EQUAL(3,sema.maxCount);
  TEST_ASSERT_EQUAL_PTR(&taskA,sema.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(&taskB,sema.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(&taskB,taskA.next);
  TEST_ASSERT_EQUAL_PTR(NULL,taskB.next);
}

void test_upSemaphore_given_sema_count_is_0_taskA_able_plus_count_by_1_for_twice(void){
  Semaphore sema;
  TCB taskA = {0};
  runningTCB = &taskA;
  
  initSemaphore(&sema,3);
  sema.count = 0;
  upSemaphore(&sema);
  
  TEST_ASSERT_EQUAL(1,sema.count);
  TEST_ASSERT_EQUAL(3,sema.maxCount);
  TEST_ASSERT_EQUAL_PTR(NULL,sema.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL,sema.waitingQueue.tail);
  
  upSemaphore(&sema);
  
  TEST_ASSERT_EQUAL(2,sema.count);
  TEST_ASSERT_EQUAL(3,sema.maxCount);
  TEST_ASSERT_EQUAL_PTR(NULL,sema.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL,sema.waitingQueue.tail);
}

void test_upSemaphore_given_sema_count_is_2_taskA_able_plus_count_by_1_for_twice_and_wake_up_taskB(void){
  Semaphore sema;
  TCB taskA = {0};
  TCB taskB = {0};
  runningTCB = &taskA;
  
  initSemaphore(&sema,3);
  sema.count = 2;
  sema.waitingQueue.head = &taskB;
  sema.waitingQueue.tail = &taskB;
  upSemaphore(&sema);
  
  TEST_ASSERT_EQUAL(3,sema.count);
  TEST_ASSERT_EQUAL(3,sema.maxCount);
  TEST_ASSERT_EQUAL_PTR(NULL,sema.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL,sema.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(&taskB,readyQueue.head);
  TEST_ASSERT_EQUAL_PTR(&taskB,readyQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL,taskB.next);
}

void test_upSemaphore_given_sema_count_is_3_taskA_not_able_plus_count_by_1_and_do_nothing(void){
  Semaphore sema;
  TCB taskA = {0};
  runningTCB = &taskA;
  
  initSemaphore(&sema,3);
  sema.count = 3;
  upSemaphore(&sema);
  
  TEST_ASSERT_EQUAL(3,sema.count);
  TEST_ASSERT_EQUAL(3,sema.maxCount);
  TEST_ASSERT_EQUAL_PTR(NULL,sema.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL,sema.waitingQueue.tail);
}