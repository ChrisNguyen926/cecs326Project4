/**
 * FCFS scheduling
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "task.h"
#include "list.h"
#include "cpu.h"
#include "schedulers.h"

/*
 * Your code and design here:
 */

struct node *head = NULL;

// create new task and add it in order
void add(char *name, int priority, int burst) {
    Task *newTask = malloc(sizeof(Task));
    if (!newTask) return;

    newTask->burst = burst;
    newTask->name = strdup(name);
    newTask->priority = priority;
    newTask->tid = 0;

    // insert(&head, newTask);

    struct node *newNode = malloc(sizeof(struct node));
    if (!newNode) {
        free(newTask->name);
        free(newTask);
        return;
    }


    // implement fcfs 
    newNode->task = newTask;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        struct node *tempNode = head;
        while (tempNode->next != NULL) {
        tempNode = tempNode->next;
    }

    tempNode->next = newNode; 
    }
}

Task* pickNextTask() {
    // return head node as it was first entered
    if (head == NULL) return NULL;
    return head->task;
}

// run the task and free memory
void schedule () {
    printf("FCFS Scheduling\n\n");

    while(head != NULL) {
        struct node *tempNode = head;
        Task *newTask = tempNode->task;
        run(newTask, newTask->burst);
        head = head->next;

        if (newTask->name != NULL) free(newTask->name);
        free(newTask);
        free(tempNode);


    }
}