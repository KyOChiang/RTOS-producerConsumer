#include <stdio.h>
#include "PriorityLinkedList.h"
#include "TaskControlBlock.h"
#include "Type.h"

void addPriorityLinkedList(PriorityLinkedList *list, void *data, int compare(void *, void *)){
	int count = 0;
	Element *temp;
	Element *subTemp;
	Element *headTemp = list->head;
	if(data!=NULL){
		if(headTemp == NULL){
			if(compare(data,headTemp) == 1){
				list->head = data; list->tail = data;
				printf("Add new task to head.\n");
			}
		}else if(headTemp != NULL){
			while(headTemp != NULL){
				if(compare(data,headTemp) == 1){
					temp = headTemp;
					if(count>0) subTemp->next = data;
					else list->head = data;
					((Element *)data)->next = temp;
					printf("Add new task\n");
					headTemp = NULL;
				}else if(compare(data,headTemp) == 0){
				printf("2\n");
					if(headTemp->next == NULL){
						headTemp->next = data; list->tail = data;
						headTemp = NULL;
						printf("insert after task\n");
					}
					else{
						printf("3\n");
						subTemp = headTemp; headTemp = headTemp->next;
					}
				}count++;
			}	
		}
	}printf("should not do anything if data is NULL\n\n");
}

void* removePriorityLinkedList(PriorityLinkedList *list, void *data, int compare(void *, void *)){
    return 0;
}

void* removeFromHeadPriorityLinkedList(PriorityLinkedList *list){
    return 0;
}