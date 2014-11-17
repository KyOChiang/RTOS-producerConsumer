#ifndef PriorityLinkedList_H
#define PriorityLinkedList_H

#include "TaskControlBlock.h"

typedef struct Element Element;
struct Element{
	void* next;
};

typedef struct PriorityLinkedList PriorityLinkedList;
struct PriorityLinkedList{
	void* head;
	void* tail;
};

void addPriorityLinkedList(PriorityLinkedList *list, void *data, int compare(void *, void *));
void* removePriorityLinkedList(PriorityLinkedList *list, void *data, int compare(void *, void *));
void* removeFromHeadPriorityLinkedList(PriorityLinkedList *list);

#define addTCB(list,data) addPriorityLinkedList(list,data,compareTCBPriority);


#endif // PriorityLinkedList_H
