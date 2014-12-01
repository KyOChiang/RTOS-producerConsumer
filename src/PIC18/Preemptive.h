/* 
 * File:   Preemptive.h
 * Author: D300-01
 *
 * Created on November 3, 2014, 2:30 PM
 */

#ifndef PREEMPTIVE_H
#define	PREEMPTIVE_H
#include "TaskControlBlock.h"
#include "PriorityLinkedList.h"
extern PriorityLinkedList readyQueue;
extern TCB *runningTCB;
void taskOne(void);
void taskTwo(void);
void initPreemptiveMultitasking(void);
#endif	/* PREEMPTIVE_H */

