#include "unity.h"
#include "Tasking.h"
#include "TaskControlBlock.h"
#include "Preemptive.h"
#include "PriorityLinkedList.h"
#include <stdio.h>
#include "producerConsumer.h"
#include "semaphore.h"
#include "Mutex.h"

void setUp(void){}

void tearDown(void){}


void test_addItemToBuffer_should_add_item_until_buffer_full(){
  init();
  addItemToBuffer();
  printf("Item : %d at ", itemBuffer[number-1]);
  printf("index %d\n", number-1);
  
  addItemToBuffer();
  printf("Item : %d at ", itemBuffer[number-1]);
  printf("index %d\n", number-1);
  
  addItemToBuffer();
  printf("Item : %d at ", itemBuffer[number-1]);
  printf("index %d\n", number-1);
  
  // Because buffer only can consist 3 data, cannot add item any more after 3rd time
  // Will print "Buffer full"
  addItemToBuffer();
}

void test_retrieveItemFromBuffer_to_retrieve_3_items_store_in_buffer_in_previous_case(){
  unsigned char itemReturned;
  //Start to retrieve item from buffer
  itemReturned = retrieveItemFromBuffer();
  printf("Item returned : %d\n",itemReturned);
  
  itemReturned = retrieveItemFromBuffer();
  printf("Item returned : %d\n",itemReturned);
  
  itemReturned = retrieveItemFromBuffer();
  printf("Item returned : %d\n",itemReturned);
  
  retrieveItemFromBuffer();
}

void test_producer_to_produce_3_items_in_buffer_and_get_blocked_when_produce_4th_item(){
  TCB producerA = {.taskID = 1};
  int yieldList[] = {9,9,9,1};
  
  initToYieldList(yieldList, 4);
  init();
  
  runningTCB = &producerA;
  producer();
  
  TEST_ASSERT_EQUAL(1, filledCount.count);
  TEST_ASSERT_EQUAL(2, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
	TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.tail);
  
  producer();
  
  TEST_ASSERT_EQUAL(2, filledCount.count);
  TEST_ASSERT_EQUAL(1, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
	TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.tail);
  
  producer();
  
  TEST_ASSERT_EQUAL(3, filledCount.count);
  TEST_ASSERT_EQUAL(0, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
	TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.tail);
  
  producer();
  
  TEST_ASSERT_EQUAL(3, filledCount.count);
  TEST_ASSERT_EQUAL(0, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(&producerA, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(&producerA, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.head);
}

//No data in buffer, but consumer try to consume data, so it get blocked
void test_consumer_should_get_blocked_at_start_because_no_data_in_buffer_yet(){
  TCB consumerA = {.taskID = 1};
  int yieldList[] = {2};
  
  initToYieldList(yieldList, 1);
  init();
  
  runningTCB = &consumerA;
  consumer();
  
  TEST_ASSERT_EQUAL(0, filledCount.count);
  TEST_ASSERT_EQUAL(3, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(&consumerA, filledCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(&consumerA, filledCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
}

void test_consumer_able_to_preempt_producer_and_consume_1_data_and_both_should_not_get_blocked(){
  TCB producerA = {.taskID = 1};
  TCB consumerA = {.taskID = 1};
  int yieldList[] = {9,10};
  
  initToYieldList(yieldList, 2);
  init();
  
  runningTCB = &producerA;
  producer();
  
  runningTCB = &consumerA;
  consumer();
  
  TEST_ASSERT_EQUAL(0, filledCount.count);
  TEST_ASSERT_EQUAL(3, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
}

void test_producer_to_wake_consumer_up(){
  TCB producerA = {.taskID = 1};
  TCB consumerA = {.taskID = 1};
  int yieldList[] = {2,9,9,9};
  readyQueue.head = NULL;
  readyQueue.tail = NULL;
  initToYieldList(yieldList, 4);
  init();
  
  runningTCB = &consumerA;
  consumer();
  
  TEST_ASSERT_EQUAL(0, filledCount.count);
  TEST_ASSERT_EQUAL(3, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(&consumerA, filledCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(&consumerA, filledCount.waitingQueue.tail);
  
  runningTCB = &producerA;
  producer();
  
  TEST_ASSERT_EQUAL(1, filledCount.count);
  TEST_ASSERT_EQUAL(2, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
	TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(&consumerA, readyQueue.head);
	TEST_ASSERT_EQUAL_PTR(&consumerA, readyQueue.tail);
  
  producer();
  
  TEST_ASSERT_EQUAL(2, filledCount.count);
  TEST_ASSERT_EQUAL(1, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
	TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.tail);
  
  producer();
  
  TEST_ASSERT_EQUAL(3, filledCount.count);
  TEST_ASSERT_EQUAL(0, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
	TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.tail);
}

void test_consumer_to_wake_producer_up(){
  TCB producerA = {.taskID = 1};
  TCB consumerA = {.taskID = 1};
  int yieldList[] = {9,9,9,1,10,10,10};
  readyQueue.head = NULL;
  readyQueue.tail = NULL;
  initToYieldList(yieldList, 7);
  init();
  
  runningTCB = &producerA;
  producer();
  
  TEST_ASSERT_EQUAL(1, filledCount.count);
  TEST_ASSERT_EQUAL(2, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
	TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.tail);
  
  producer();
  
  TEST_ASSERT_EQUAL(2, filledCount.count);
  TEST_ASSERT_EQUAL(1, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
	TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.tail);
  
  producer();
  
  TEST_ASSERT_EQUAL(3, filledCount.count);
  TEST_ASSERT_EQUAL(0, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
	TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.tail);
  
  producer();
  
  TEST_ASSERT_EQUAL(3, filledCount.count);
  TEST_ASSERT_EQUAL(0, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(&producerA, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(&producerA, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.head);
  
  runningTCB = &consumerA;
  consumer();
  
  TEST_ASSERT_EQUAL(2, filledCount.count);
  TEST_ASSERT_EQUAL(1, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(&producerA, readyQueue.head);
	TEST_ASSERT_EQUAL_PTR(&producerA, readyQueue.tail);
  
  consumer();
  
  TEST_ASSERT_EQUAL(1, filledCount.count);
  TEST_ASSERT_EQUAL(2, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.head);
  
  consumer();
  
  TEST_ASSERT_EQUAL(0, filledCount.count);
  TEST_ASSERT_EQUAL(3, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.head);
}

//producer A and B produce item until buffer full and producer A get blocked
//consumer A and B start to consume item and wake producer A
//Now consumer A get blocked and producer A help to wake consumer A up
void test_producer_and_consumer_with_multiple_producer_and_consumer(){
  TCB producerA = {.taskID = 1};
  TCB producerB = {.taskID = 1};
  TCB consumerA = {.taskID = 1};
  TCB consumerB = {.taskID = 1};
  int yieldList[] = {9,9,9,1,10,10,10,2,1};
  readyQueue.head = NULL;
  readyQueue.tail = NULL;
  initToYieldList(yieldList, 9);
  init();
  
  runningTCB = &producerA;
  producer();
  
  TEST_ASSERT_EQUAL(1, filledCount.count);
  TEST_ASSERT_EQUAL(2, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
	TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.tail);
  
  runningTCB = &producerB;
  producer();
  
  TEST_ASSERT_EQUAL(2, filledCount.count);
  TEST_ASSERT_EQUAL(1, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
	TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.tail);
  
  producer();
  
  TEST_ASSERT_EQUAL(3, filledCount.count);
  TEST_ASSERT_EQUAL(0, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
	TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.tail);
  
  runningTCB = &producerA;
  producer();
  
  TEST_ASSERT_EQUAL(3, filledCount.count);
  TEST_ASSERT_EQUAL(0, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(&producerA, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(&producerA, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.head);
  
  runningTCB = &consumerB;
  consumer();
  
  TEST_ASSERT_EQUAL(2, filledCount.count);
  TEST_ASSERT_EQUAL(1, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(&producerA, readyQueue.head);
	TEST_ASSERT_EQUAL_PTR(&producerA, readyQueue.tail);
  
  runningTCB = &consumerA;
  consumer();
  
  TEST_ASSERT_EQUAL(1, filledCount.count);
  TEST_ASSERT_EQUAL(2, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.head);
  
  consumer();
  
  TEST_ASSERT_EQUAL(0, filledCount.count);
  TEST_ASSERT_EQUAL(3, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.head);
  
  consumer();
  
  TEST_ASSERT_EQUAL(0, filledCount.count);
  TEST_ASSERT_EQUAL(3, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(&consumerA, filledCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(&consumerA, filledCount.waitingQueue.head);
  
  runningTCB = &producerA;
  producer();
  
  TEST_ASSERT_EQUAL(1, filledCount.count);
  TEST_ASSERT_EQUAL(2, emptyCount.count);
  TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.head);
	TEST_ASSERT_EQUAL_PTR(NULL, emptyCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, filledCount.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(&producerA, readyQueue.head);
	TEST_ASSERT_EQUAL_PTR(&consumerA, readyQueue.tail);
	TEST_ASSERT_EQUAL_PTR(&consumerA, producerA.next);
}





