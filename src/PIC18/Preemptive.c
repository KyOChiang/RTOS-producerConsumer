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

TCB *runningTCB;
TCB tcb[3];

void taskOne(){
    int count = 0;
    while(1){
        count++;
    }
}

void taskTwo(){
    int count = -1;
    while(1){
        count--;
    }
}

void initPriorityMultitasking(){
    runningTCB = &tcb[0];
    tcb[1].task = taskOne;
    tcb[2].task = taskTwo;
    //Add taskOne and tasktwo TCBs into the priority linkedlist
    while(1);
}

