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
    newTask->name = strdup(name);
    newTask->priority = priority;
    newTask->burst = burst;
    newTask->tid = 0;

    // insert(&head, t);

    struct node *newNode = malloc(sizeof(struct node));
    if (!newNode) {
        free(newTask->name);
        free(newTask);
        return;
    }
    newNode->task = newTask;
    newNode->next = NULL;

    // fcfs
    if (head == NULL) {
        head = newNode;
    } else {
        struct node *cur = head;
        while (cur->next != NULL) cur = cur->next;
        cur->next = newNode;
    }
}

// return the task at the head
Task* pickNextTask() {
    if (head == NULL) return NULL;
    return head->task;
}

// run, free node and task
void schedule() {
    while (head != NULL) {
        struct node *cur = head;
        Task *newTask = cur->task;

        run(newTask, newTask->burst);

        head = head->next;

        if (newTask->name) free(newTask->name);
        free(newTask);
        free(cur);
    }
}