#ifndef SEVENSEG_H_
#define SEVENSEG_H_

typedef enum{
    _7SEG_INIT,
    _7SEG_WAITING
}_7SEG_STATE;

typedef struct{
    unsigned long clock;
    _7SEG_STATE state;
    int counter;
}_7SEG;

void init7SegmentHW();
void init7Segment(_7SEG* _7seg);
void _7SegmentSM(_7SEG* _7seg);
void write7Segment(char data);
#endif // SEVENSEG_H_