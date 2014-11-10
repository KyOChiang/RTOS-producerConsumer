#include "unity.h"
#include "SevenSeg.h"
#include "p18f4520.h"
#include "mock_spi.h"
#include "mock_timers.h"
#include "mock_Clock.h"

void setUp(void){}

void tearDown(void){}

void test_init7Segment_to_reinitialize_state_of_7Seg(){
	_7SEG sevenSEG = {.clock = 0, .state = _7SEG_WAITING, .counter = 0xff};
	init7Segment(&sevenSEG);
	TEST_ASSERT_EQUAL(_7SEG_INIT,sevenSEG.state);
}

void test_7SegmentSM_to_init7SegmentHW_and_get_appropriate_data_into_7Seg(){
	_7SEG sevenSEG = {.clock = 0, .state = _7SEG_INIT, .counter = 0xff};
	OpenSPI_Expect(SPI_FOSC_4, MODE_11, SMPEND);
	getCLOCK_ExpectAndReturn(110);
	WriteSPI_ExpectAndReturn(0x77,0x77);
	_7SegmentSM(&sevenSEG);
	
	TEST_ASSERT_EQUAL(_7SEG_WAITING,sevenSEG.state);
	TEST_ASSERT_EQUAL(110,sevenSEG.clock);
	TEST_ASSERT_EQUAL(0,sevenSEG.counter);
}

void test_7SegmentSM_should_display_1_at_7_segment_display_after_150ms(){
	_7SEG sevenSEG = {.clock = 150, .state = _7SEG_WAITING, .counter = 0x00};
	getCLOCK_ExpectAndReturn(638);
	getCLOCK_ExpectAndReturn(638);
	WriteSPI_ExpectAndReturn(0x77,0x77);
	_7SegmentSM(&sevenSEG);
	
	TEST_ASSERT_EQUAL(_7SEG_WAITING,sevenSEG.state);
	TEST_ASSERT_EQUAL(638,sevenSEG.clock);
	TEST_ASSERT_EQUAL(1,sevenSEG.counter);
}

void test_7SegmentSM_should_do_nothing_if_150ms_interval_not_passed(){
	_7SEG sevenSEG = {.clock = 150, .state = _7SEG_WAITING, .counter = 0x01};
	getCLOCK_ExpectAndReturn(280);
	_7SegmentSM(&sevenSEG);
	
	TEST_ASSERT_EQUAL(_7SEG_WAITING,sevenSEG.state);
	TEST_ASSERT_EQUAL(150,sevenSEG.clock);
	TEST_ASSERT_EQUAL(1,sevenSEG.counter);
}

void test_7SegmentSM_should_display_0_at_7_segment_display_after_0x0f(){
	_7SEG sevenSEG = {.clock = 150, .state = _7SEG_WAITING, .counter = 0x0f};
	getCLOCK_ExpectAndReturn(638);
	getCLOCK_ExpectAndReturn(638);
	WriteSPI_ExpectAndReturn(0x1e,0x1e);
	_7SegmentSM(&sevenSEG);
	
	TEST_ASSERT_EQUAL(_7SEG_WAITING,sevenSEG.state);
	TEST_ASSERT_EQUAL(638,sevenSEG.clock);
	TEST_ASSERT_EQUAL(0,sevenSEG.counter);
}




