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
