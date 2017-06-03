#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE
#include "minHeap.h"

typedef struct priorityQueue {
    unsigned int id ;
    unsigned int size ;
    minHeap indexes ;
    minHeap *ranges ;
} priorityQueue ;

priorityQueue initPriorityQueue();
void push(priorityQueue *pq, int key);
node pop(priorityQueue *pq);
node peek(priorityQueue *pq);
int isEmpty (priorityQueue *pq);
void freeQueue(priorityQueue *pq);
int testQueue();

#endif
