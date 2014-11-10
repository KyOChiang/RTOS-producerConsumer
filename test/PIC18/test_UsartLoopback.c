#include "unity.h"
#include "UsartLoopback.h"
#include "mock_usart.h"

void setUp(void){}

void tearDown(void){}

void test_uartLoopbackSM_given_WAIT_DATA_should_stay_in_same_state(void){
	LoopbackData data = {WAIT_DATA,0};
	DataRdyUSART_ExpectAndReturn(0);
	
	usartLoopbackSM(&data);
	TEST_ASSERT_EQUAL(WAIT_DATA,data.state);
}

void test_uartLoopbackSM_given_WAIT_DATA_should_go_next_state_if_data_arrived(void){
	LoopbackData data = {WAIT_DATA,0};
	// Mock cant mock define macro, only function available, unless redefine in usart.h
	DataRdyUSART_ExpectAndReturn(1);
	getcUSART_ExpectAndReturn(0x5a);
	
	usartLoopbackSM(&data);
	TEST_ASSERT_EQUAL(WAIT_TO_TX,data.state);
	TEST_ASSERT_EQUAL(0x5a,data.dataByte);
}

void test_uartLoopbackSM_given_WAIT_TO_TX_should_stay_in_same_state(void){
	LoopbackData data = {WAIT_TO_TX,0};
	BusyUSART_ExpectAndReturn(1);
	
	usartLoopbackSM(&data);
	TEST_ASSERT_EQUAL(WAIT_TO_TX,data.state);
}

void test_uartLoopbackSM_given_WAIT_TO_TX_should_go_WAIT_DATA_after_send_back_data(void){
	LoopbackData data = {WAIT_TO_TX,0x5a};
	BusyUSART_ExpectAndReturn(0);
	putcUSART_Expect(0x5a);
	usartLoopbackSM(&data);
	TEST_ASSERT_EQUAL(WAIT_DATA,data.state);
}