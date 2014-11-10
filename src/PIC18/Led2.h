#ifndef Led2_H
#define Led2_H

typedef enum {
  LED_UNKNOWN_STATUS,
  LED_OFF,
  LED_ON
} Led2Status;

typedef struct Led2Data Led2Data;

struct Led2Data {
  int state;
  Led2Status ledStatus;
  unsigned long currentClock;
};

void led2SM(Led2Data *data) ;

#endif // Led2_H
