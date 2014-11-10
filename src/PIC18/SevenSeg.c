#include "SevenSeg.h"
#include "..\\18c.h"
#include "Clock.h"

#define   SMPEND        0b10000000  
#define   MODE_11       0b00000011 
#define   SPI_FOSC_4    0b00000000

#define ON_DISPLAY() (PORTDbits.RD0 = 1)
#define OFF_DISPLAY() (PORTDbits.RD0 = 0)
#define TRISD0Out() (TRISDbits.RD0 = 0)
#define MS_500 488 //Around 500 millisec

char hexPattern[] = {  0x77, //0
                       0x41, //1
                       0x3b, //2
                       0x6b, //3
                       0x4d, //4
                       0x6e, //5
                       0x7e, //6
                       0x43, //7
                       0x7f, //8
                       0x6f, //9
                       0x5f, //a
                       0x7c, //b
                       0x38, //c
                       0x79, //d
                       0x3e, //e
                       0x1e, //f
};

void write7Segment(char data){
    WriteSPI(hexPattern[data]);
}

void init7Segment(_7SEG* _7seg){
    _7seg->state = _7SEG_INIT;
    _7seg->clock = 0;
    _7seg->counter = 0;
}

void init7SegmentHW(){
    OpenSPI(SPI_FOSC_4, MODE_11, SMPEND);
    TRISD0Out();
    ON_DISPLAY();
}

void _7SegmentSM(_7SEG* _7seg){
    switch(_7seg->state){
        case _7SEG_INIT   :
            init7SegmentHW();
            _7seg->counter = 0;
            _7seg->clock = getCLOCK();
            _7seg->state = _7SEG_WAITING;
            write7Segment(_7seg->counter);
            break;
        case _7SEG_WAITING :
            if(getCLOCK() - _7seg->clock == MS_500){
		_7seg->clock = getCLOCK();
                write7Segment(_7seg->counter);
                _7seg->counter += 1;
            }
            if(_7seg->counter == 16)
                    _7seg->counter = 0;
            break;
        default : break ;
    }
}