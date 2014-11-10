#include "unity.h"
#include "Clock.h"
#include "p18f4520.h"
#include "mock_timers.h"

#define TIMER_INT_OFF  0b01111111  //Disable TIMER Interrupt
#define T0_8BIT        0b11111111  //Timer0 is configured as an 8-bit timer/counter
#define T0_SOURCE_INT  0b11011111  //Internal instruction cycle clock (CLKO) acts as source of clock
#define T0_PS_1_8      0b11110010  //1:8 Prescale value

void setUp(void)
{
}

void tearDown(void)
{
}

void test_initClock_with_8_bit_mode_with_internal_clock_with_prescaler_value_1_to_8() {
  clock = 10000;
  OpenTimer0_Expect( TIMER_INT_OFF &
              T0_8BIT &
              T0_SOURCE_INT &
              T0_PS_1_8);
  initClock();
  TEST_ASSERT_EQUAL(0, clock);
}

void test_hasTimer0Overflowed_given_not_yet_overflowed_should_return_FALSE(void) {
	INTCONbits.TMR0IF = 0;
  TEST_ASSERT_FALSE(hasTimer0Overflowed());
}

void test_hasTimer0Overflowed_given_overflowed_should_return_TRUE(void) {
	INTCONbits.TMR0IF = 1;
  TEST_ASSERT_TRUE(hasTimer0Overflowed());
}

void test_clearTimer0Overflowed_given_overflowed_should_clear_overflow_flag(void) {
	INTCONbits.TMR0IF = 1;
  clearTimer0Overflowed();
  TEST_ASSERT_FALSE(INTCONbits.TMR0IF);
}
