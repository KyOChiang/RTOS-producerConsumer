#include "unity.h"
#include "PriorityLinkedList.h"
#include "TaskControlBlock.h"

void setUp(void){}

void tearDown(void){}

void test_addPriorityLinkedList_should_insert_task_to_Priority_Linked_List_if_task1_has_low_priority_than_taskA(void){
	TCB taskA = {.next=NULL, .priority = 1};
	TCB task1 = {.next=NULL, .priority = 4};
	PriorityLinkedList LL = {.head = &task1, .tail = &task1};
	
	addTCB(&LL,&taskA);
	TEST_ASSERT_EQUAL(&taskA,LL.head);
	TEST_ASSERT_EQUAL(&task1,LL.tail);
	TEST_ASSERT_EQUAL(&task1,taskA.next);
	TEST_ASSERT_EQUAL(NULL,task1.next);
}

void test_addPriorityLinkedList_should_insert_task_to_Priority_Linked_List_if_head_is_NULL(void){
	TCB taskA = {.next=NULL, .priority = 1};
	PriorityLinkedList LL = {.head = NULL, .tail = NULL};
	addTCB(&LL,&taskA);
	TEST_ASSERT_EQUAL(&taskA,LL.head);
	TEST_ASSERT_EQUAL(&taskA,LL.tail);
	TEST_ASSERT_EQUAL(NULL,taskA.next);
}

void test_addPriorityLinkedList_should_do_nothing_to_Priority_Linked_List(void){
	TCB task1 = {.next=NULL, .priority = 4};
	PriorityLinkedList LL = {.head = &task1, .tail = &task1};
	
	addTCB(&LL,NULL);
	TEST_ASSERT_EQUAL(&task1,LL.head);
	TEST_ASSERT_EQUAL(&task1,LL.tail);
	TEST_ASSERT_EQUAL(NULL,task1.next);
}

void test_addPriorityLinkedList_should_insert_new_task_after_task_1(void){
	TCB taskA = {.next=NULL, .priority = 18};
	TCB task1 = {.next=NULL, .priority = 4};
	PriorityLinkedList LL = {.head = &task1, .tail = &task1};
	
	addTCB(&LL,&taskA);
	TEST_ASSERT_EQUAL(&task1,LL.head);
	TEST_ASSERT_EQUAL(&taskA,LL.tail);
	TEST_ASSERT_EQUAL(&taskA,task1.next);
	TEST_ASSERT_EQUAL(NULL,taskA.next);
}

void test_addPriorityLinkedList_should_insert_new_task_in_between_task_1_and_task_2(void){
	TCB taskA = {.next=NULL, .priority = 7};
	TCB task2 = {.next=NULL, .priority = 9};
	TCB task1 = {.next=&task2, .priority = 4};
	
	PriorityLinkedList LL = {.head = &task1, .tail = &task2};
	
	addTCB(&LL,&taskA);
	TEST_ASSERT_EQUAL(&task1,LL.head);
	TEST_ASSERT_EQUAL(&task2,LL.tail);
	TEST_ASSERT_EQUAL(&taskA,task1.next);
	TEST_ASSERT_EQUAL(&task2,taskA.next);
	TEST_ASSERT_EQUAL(NULL,task2.next);
}

void test_addPriorityLinkedList_should_insert_new_task_in_after_task_1_and_task_2(void){
	TCB taskA = {.next=NULL, .priority = 11};
	TCB task2 = {.next=NULL, .priority = 9};
	TCB task1 = {.next=&task2, .priority = 4};
	
	PriorityLinkedList LL = {.head = &task1, .tail = &task2};
	
	addTCB(&LL,&taskA);
	TEST_ASSERT_EQUAL(&task1,LL.head);
	TEST_ASSERT_EQUAL(&taskA,LL.tail);
	TEST_ASSERT_EQUAL(&task2,task1.next);
	TEST_ASSERT_EQUAL(&taskA,task2.next);
	TEST_ASSERT_EQUAL(NULL,taskA.next);
}

void test_addPriorityLinkedList_should_insert_new_task_in_after_task_1_and_task_2_same_prior(void){
	TCB *returnTCB;
	TCB taskA = {.next=NULL, .priority = 9};
	TCB task2 = {.next=NULL, .priority = 9};
	TCB task1 = {.next=&task2, .priority = 9};
	// task1>task2>taskA
	PriorityLinkedList LL = {.head = &task1, .tail = &task2};
	returnTCB = removeFromHeadPriorityLinkedList(&LL);
	addTCB(&LL,&taskA);
	returnTCB = removeFromHeadPriorityLinkedList(&LL);
	addTCB(&LL,&task1);
	returnTCB = removeFromHeadPriorityLinkedList(&LL);
	addTCB(&LL,&task2);
	returnTCB = removeFromHeadPriorityLinkedList(&LL);
	addTCB(&LL,&taskA);
	returnTCB = removeFromHeadPriorityLinkedList(&LL);
	addTCB(&LL,&task1);
	returnTCB = removeFromHeadPriorityLinkedList(&LL);
	addTCB(&LL,&task2);
}

void test_addPriorityLinkedList_should_insert_2_new_task_after_task_1_and_before_task_2(void){
	TCB taskB = {.next=NULL, .priority = 1};
	TCB taskA = {.next=NULL, .priority = 7};
	TCB task2 = {.next=NULL, .priority = 9};
	TCB task1 = {.next=&task2, .priority = 4};
	
	PriorityLinkedList LL = {.head = &task1, .tail = &task2};
	
	addTCB(&LL,&taskA);
	addTCB(&LL,&taskB);
	TEST_ASSERT_EQUAL(&taskB,LL.head);
	TEST_ASSERT_EQUAL(&task2,LL.tail);
	TEST_ASSERT_EQUAL(&task1,taskB.next);
	TEST_ASSERT_EQUAL(&taskA,task1.next);
	TEST_ASSERT_EQUAL(&task2,taskA.next);
	TEST_ASSERT_EQUAL(NULL,task2.next);
}

void test_removeFromHeadPriorityLinkedList_should_remove_the_first_task_from_linked_list(){
	TCB *returnTCB;
	TCB task1 = {.next=NULL, .priority = 4};
	PriorityLinkedList LL = {.head = &task1, .tail = &task1};
	
	returnTCB = removeFromHeadPriorityLinkedList(&LL);
	TEST_ASSERT_EQUAL(NULL,LL.head);
	TEST_ASSERT_EQUAL(NULL,LL.tail);
	TEST_ASSERT_EQUAL(&task1,returnTCB);
}

void test_removeFromHeadPriorityLinkedList_should_remove_the_first_task_from_both_task(){
	TCB *returnTCB;
	TCB task2 = {.next=NULL, .priority = 4};
	TCB task1 = {.next=&task2, .priority = 4};
	PriorityLinkedList LL = {.head = &task1, .tail = &task2};
	
	returnTCB = removeFromHeadPriorityLinkedList(&LL);
	TEST_ASSERT_EQUAL(&task2,LL.head);
	TEST_ASSERT_EQUAL(&task2,LL.tail);
	TEST_ASSERT_EQUAL(&task1,returnTCB);
}

void test_removeFromHeadPriorityLinkedList_should_return_NULL_if_empty_TCB_in_list(){
	TCB *returnTCB;
	PriorityLinkedList LL = {.head = NULL, .tail = NULL};
	
	returnTCB = removeFromHeadPriorityLinkedList(&LL);
	TEST_ASSERT_EQUAL(NULL,LL.head);
	TEST_ASSERT_EQUAL(NULL,LL.tail);
	TEST_ASSERT_EQUAL(NULL,returnTCB);
}

