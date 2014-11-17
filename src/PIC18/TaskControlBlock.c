#include <stdio.h>
#include "TaskControlBlock.h"
#include "Type.h"

int compareTCBPriority(void *elementOfInterest, void *elementInList){
	TCB* EOI;
	TCB* EIL;
	
	EOI = (TCB *)elementOfInterest;
	EIL = (TCB *)elementInList;

	if(EOI != NULL && EIL == NULL)
		return 1;
	if(EOI != NULL && EIL != NULL){
		if(EOI->priority < EIL->priority)
			return 1;
		else if(EOI->priority == EIL->priority)
			return 0;
		else if(EOI->priority > EIL->priority)
			return 0;
	}	
	else return 0;
        return 0;
}
