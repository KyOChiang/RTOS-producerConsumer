/*
 * File:   Main.c
 * Author: Chiang Choon Yong
 *
 * Created on September 29, 2014, 11:19 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "..\\18c.h"
#include "Preemptive.h"
#include "TaskControlBlock.h"
#include "PriorityLinkedList.h"
#include "Type.h"

#if !(defined(__XC) || defined(__18CXX))
  #include "usart.h"
  #include "spi.h"
  #include "timers.h"
#else
  #include <usart.h>
  #include <spi.h>
  #include <timers.h>
#endif // __18CXX

void taskOne(void);
void taskTwo(void);

TCB *runningTCB;
TCB allTcbs[3];
PriorityLinkedList readyQueue;
uint8 stacks[2][80];

void createTask(TCB tcbs[],int index, void (* task)(void)){
    tcbs[index].next = NULL;
    tcbs[index].priority = 0;
    tcbs[index].task = (uint16)task;
    tcbs[index].taskID = index;
    addTCB(&readyQueue, &allTcbs[index]);
}

void taskOne(void){
    int count = 0;
    while(1){
        count++;
    }
}

void taskTwo(void){
    int count = -1;
    while(1){
        count--;
    }
}

void initPreemptiveMultitasking(void){
    readyQueue->head = NULL;
    readyQueue->tail = NULL;
    runningTCB = &allTcbs[0];
    runningTCB->next = 0;
    runningTCB->priority = 0;
    runningTCB->taskID = 0;
    createTask(allTcbs, 1, taskOne);
    createTask(allTcbs, 2, taskTwo);
    //Add taskOne and tasktwo TCBs into the priority linkedlist
}

