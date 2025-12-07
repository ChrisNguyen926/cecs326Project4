/**
 * Round-robin scheduling
 */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "task.h"
#include "list.h"
#include "cpu.h"


/*
 * Your code and design here:
 */

// Head and tail of the task list
struct node *head = NULL;
struct node *tail = NULL;

// Add a task to the list
void add(char *name, int priority, int burst) {
    Task *newTask = malloc(sizeof(Task));
    newTask->name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(newTask->name, name);
    newTask->priority = priority;
    newTask->burst = burst;
    struct node *newNode = malloc(sizeof(struct node));
    newNode->task = newTask;
    newNode->next = NULL;
    
    // Insert at the end to maintain queue order using tail pointer
    if (head == NULL) {
        // First task - initialize both head and tail
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

// Pick the first task in the queue
Task *pickNextTask() {
    if (head == NULL)
        return NULL;
    return head->task;
}

// Invoke the scheduler
void schedule() {
    printf("Round-Robin Scheduling\n\n");
    
    // Execute tasks using round-robin with time quantum
    while (head != NULL) {
        Task *current = pickNextTask();
        int slice = (current->burst > QUANTUM) ? QUANTUM : current->burst;
        // Run the task for the time slice
        run(current, slice);
        current->burst -= slice;
        // If task is not complete, move it to the end of the queue
        if (current->burst > 0) {
            delete(&head, current);           
            struct node *newNode = malloc(sizeof(struct node));
            newNode->task = current;
            newNode->next = NULL;    
            if (head == NULL) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        } else {
            // Task is complete, remove it from the list
            delete(&head, current);
            
            // Update tail if list is now empty
            if (head == NULL) {
                tail = NULL;
            }
            free(current->name);
            free(current);
        }
    }
}
