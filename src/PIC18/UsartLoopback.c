#include "UsartLoopback.h"
#include "usart.h"
/**
 *	Initialize the uart Loopback's internal data
 */
void initUsartLoopback(LoopbackData *data){
	data->state = WAIT_DATA;
	data->dataByte = '0';
}

void usartLoopbackSM(LoopbackData *data){
	switch(data->state){
		case WAIT_DATA:
			if(DataRdyUSART()){
				data->dataByte = getcUSART();
				data->state = WAIT_TO_TX;
			}
			break;
		case WAIT_TO_TX:
			if(!BusyUSART()){
				data->state = WAIT_DATA;
				putcUSART(data->dataByte);
			}
			break;
		default:
			// should not reach here
			break;
	}
}