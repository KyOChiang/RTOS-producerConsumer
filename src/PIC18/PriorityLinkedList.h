#ifndef PriorityLinkedList_H
#define PriorityLinkedList_H

typedef struct PriorityLinkedList PriorityLinkedList;
struct PriorityLinkedList{
	void* head;
	void* tail;
};

void* addPriorityLinkedList(PriorityLinkedList *list, void *data, int compare(void *, void *));
void* removePriorityLinkedList(PriorityLinkedList *list, void *data, int compare(void *, void *));
void* removeFromHeadPriorityLinkedList(PriorityLinkedList *list);




#endif // PriorityLinkedList_H
