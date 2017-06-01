#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE
#include "minHeap.h"

typedef struct priorityQueue {
    int size ;
    minHeap indexes ;
    minHeap *ranges ;
} priorityQueue ;

priorityQueue initPriorityQueue();
void push(priorityQueue *pq, int key);
node pop(priorityQueue *pq);
node peek(priorityQueue *pq);
int isEmpty (priorityQueue *pq);
int testQueue();

#endif
