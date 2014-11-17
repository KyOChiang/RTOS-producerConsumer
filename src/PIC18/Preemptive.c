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

TCB *runningTCB;
TCB allTcbs[3];
PriorityLinkedList readyQueue;
uint8 stacks[2][80];
//uint8 stackOne[80];
//uint8 stackTwo[80];

void createTask(TCB tcbs[],int index, void (* task)(void)){
    addPriorityLinkedList(readyQueue, &tcbs[index]);
    tcbs[index] = taskOne;
    tcbs[index].stackPointer = (uint16)&stacks[index - 1];
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

void initPreemptiveMultitasking(){
    runningTCB = &allTcbs[0];
    createTask(allTcbs, 1, taskOne);
    createTask(allTcbs, 2, taskTwo);
    //Add taskOne and tasktwo TCBs into the priority linkedlist
    while(1);
}

