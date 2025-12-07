/*
 * Priority scheduling
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
struct node *head = NULL;

// Add a task to the list
void add(char *name, int priority, int burst) {
    // Create a new task
    Task *newTask = malloc(sizeof(Task));
    newTask->name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(newTask->name, name);
    newTask->priority = priority;
    newTask->burst = burst;
    
    // Insert task into the list 
    insert(&head, newTask);
}

// Pick the next task with the highest priority
Task *pickNextTask() {
    if (head == NULL)
        return NULL;

    struct node *temp = head;
    Task *highestPriorityTask = temp->task;
    
    // Traverse the list to find the task with highest priority
    while (temp != NULL) {
        if (temp->task->priority > highestPriorityTask->priority) {
            highestPriorityTask = temp->task;
        }
        temp = temp->next;
    }
    return highestPriorityTask;
}

// Invoke the scheduler
void schedule() {    
    printf("Priority Scheduling\n\n");

    // Execute tasks in priority order 
    while (head != NULL) {
        Task *current = pickNextTask();
        
        // Run the task for its full burst time
        run(current, current->burst);
        delete(&head, current);
        free(current->name);
        free(current);
    }
}
