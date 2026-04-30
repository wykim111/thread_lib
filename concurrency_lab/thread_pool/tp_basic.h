#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_QUEUE_SIZE 10

typedef struct task_t {
    void (*func)(void);
    void *arg;
    struct task_t* next;
} task_t;

typedef struct{
    task_t* head;
    task_t* tail;
    int size;
    
} task_queue_t;

void queue_init(task_queue_t* queue);
void queue_push(task_queue_t* queue, task_t* task);
task_queue_t* queue_pop(task_queue_t* queue);
void queue_destroy(task_queue_t* queue);