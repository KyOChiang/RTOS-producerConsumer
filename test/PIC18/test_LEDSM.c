#include "unity.h"
#include "LEDSM.h"
#include "Blinky.h"
#include "p18f4520.h"
#include "mock_Clock.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_ledInit() {
  LEDData ledData = {.state = LED_ON, .currentClock = 0};
  initLed(&ledData);
  TEST_ASSERT_EQUAL(LED_START, ledData.state);
}

void test_ledSM_given_LED_START(void) {
  LEDData ledData = {.state = LED_START, .currentClock = 0};
  getCLOCK_ExpectAndReturn(400);
  ledSM(&ledData);
  TEST_ASSERT_EQUAL(LED_OFF, ledData.state);
  TEST_ASSERT_EQUAL(400, ledData.currentClock);
}

void test_ledSM_given_LED_OFF_and_time_is_less_than_5_msec(void) {
  LEDData ledData = {.state = LED_OFF, .currentClock = 0};
  getCLOCK_ExpectAndReturn(400);
  ledSM(&ledData);
  TEST_ASSERT_EQUAL(LED_OFF, ledData.state);
  TEST_ASSERT_EQUAL(0, ledData.currentClock);
}

void test_ledSM_given_LED_OFF_and_time_is_reach_5_msec(void) {
	LEDData ledData = {.state = LED_OFF, .currentClock = 400};
  getCLOCK_ExpectAndReturn(900);
  getCLOCK_ExpectAndReturn(1000);
  ledSM(&ledData);
  TEST_ASSERT_EQUAL(LED_ON, ledData.state);
  TEST_ASSERT_EQUAL(1000, ledData.currentClock);
}

void test_ledSM_given_LED_ON_and_time_is_less_than_5_msec(void) {
	LEDData ledData = {.state = LED_ON, .currentClock = 0};
  getCLOCK_ExpectAndReturn(400);
  ledSM(&ledData);
  TEST_ASSERT_EQUAL(LED_ON, ledData.state);
  TEST_ASSERT_EQUAL(0, ledData.currentClock);
}

void test_ledSM_given_LED_ON_and_time_is_reach_5_msec(void) {
	LEDData ledData = {.state = LED_ON, .currentClock = 400};
  getCLOCK_ExpectAndReturn(900);
  getCLOCK_ExpectAndReturn(1000);
  ledSM(&ledData);
  TEST_ASSERT_EQUAL(LED_OFF, ledData.state);
  TEST_ASSERT_EQUAL(1000, ledData.currentClock);
}