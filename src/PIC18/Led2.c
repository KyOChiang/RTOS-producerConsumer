#include "Led2.h"
#include "Tasking.h"
#include "Blinky.h"
#include "Clock.h"

#define MSEC_500 488
#define MSEC_150 147

void testingLed2SM(Led2Data *data) {
    /*
  startTasking(data->state);
  printf("LED2_INIT\n");
  printf("before yield\n");
  
  if(data->ledStatus == 10) {
    yield(data->state);
    printf("after yield\n");
  } else {
    printf("take jadi yield\n");
  }
  endTasking();
     */
}

void led2SM(Led2Data *data) {
  startTasking(data->state)
  data->ledStatus = LED_ON;
  while(1) {
    if(getCLOCK() - data->currentClock >= MSEC_150){
      if(data->ledStatus == LED_ON){
        data->ledStatus = LED_OFF; offLED();
      }else if(data->ledStatus == LED_OFF){
        data->ledStatus = LED_ON; onLED();
      }data->currentClock = getCLOCK(); 
    }yield(data->state);
  }
  endTasking()
}