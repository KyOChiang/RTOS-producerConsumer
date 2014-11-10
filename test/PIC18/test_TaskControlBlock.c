#include "unity.h"
#include "TaskControlBlock.h"

void setUp(void){}

void tearDown(void){}

void test_compareTCBPriority_to_insert_first_element(void){
	int respondToInsert;
	TCB newELE = {.priority = 1};
	respondToInsert = compareTCBPriority(&newELE, NULL);
	
	TEST_ASSERT_EQUAL(1,respondToInsert);
}

void test_compareTCBPriority_to_insert_new_element_if_priority_is_higher_than_element_in_list(void){
	int respondToInsert;
	TCB newELE = {.priority = 1};
	TCB inListELE = {.priority = 2};
	respondToInsert = compareTCBPriority(&newELE, &inListELE);
	
	TEST_ASSERT_EQUAL(1,respondToInsert);
}

void test_compareTCBPriority_not_to_insert_new_element_if_priority_is_lower_than_element_in_list(void){
	int respondToInsert;
	TCB newELE = {.priority = 3};
	TCB inListELE = {.priority = 2};
	respondToInsert = compareTCBPriority(&newELE, &inListELE);
	
	TEST_ASSERT_EQUAL(0,respondToInsert);
}

void test_compareTCBPriority_return_zero_if_no_element(void){
	int respondToInsert;
	respondToInsert = compareTCBPriority(NULL, NULL);
	
	TEST_ASSERT_EQUAL(0,respondToInsert);
}

void test_compareTCBPriority_should_not_insert_if_both_elements_have_same_priority(void){
	int respondToInsert;
	TCB newELE = {.priority = 4};
	TCB inListELE = {.priority = 4};
	respondToInsert = compareTCBPriority(&newELE, &inListELE);
	
	TEST_ASSERT_EQUAL(0,respondToInsert);
}