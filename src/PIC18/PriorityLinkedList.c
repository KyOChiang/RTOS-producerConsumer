#include <stdio.h>
#include "PriorityLinkedList.h"
#include "TaskControlBlock.h"
#include "Type.h"

void addPriorityLinkedList(PriorityLinkedList *list, void *data, int compare(void *, void *)){
	int count = 0;
	Element *temp;
	Element *subTemp;
	Element *headTemp = list->head;
	// If no new task(data), do nothing
	if(data!=NULL){
		//If list->head is NULL, just insert new task into head
		if(headTemp == NULL){
			if(compare(data,headTemp) == 1){
				list->head = data; list->tail = data; }
		}else if(headTemp != NULL){
			while(headTemp != NULL){
			//If head != NULL, compare and find out can insert or not
			//If can insert, check the current head got next or not
			//1 or 2 tempVariable needed to store previous head before updated
				if(compare(data,headTemp) == 1){
					temp = headTemp;
					if(count>0) subTemp->next = data;
					else list->head = data;
					((Element *)data)->next = temp;
					headTemp = NULL;
				}else if(compare(data,headTemp) == 0){
					if(headTemp->next == NULL){
						headTemp->next = data; list->tail = data;
						headTemp = NULL;//Just want to exit the while loop/ since this is temp pointer, it
					}else{
						subTemp = headTemp; headTemp = headTemp->next;
					}
				}count++;}}}
}

void* removePriorityLinkedList(PriorityLinkedList *list, void *data, int compare(void *, void *)){
    return 0;
}

void* removeFromHeadPriorityLinkedList(PriorityLinkedList *list){
	Element *headTemp = list->head;
	if(headTemp != NULL){
		list->head = headTemp->next;
		if(headTemp->next == NULL) //if there only one TCB in linked list
			list->tail = NULL;
        headTemp->next = NULL;
	}
    return headTemp;
}