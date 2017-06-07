#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE
#include "maxHeap.h"

typedef struct priorityQueue {
    unsigned int id ;
    unsigned int size ;
    maxHeap indexes ;
    maxHeap *ranges ;
} priorityQueue ;

priorityQueue initPriorityQueue();
void push(priorityQueue *pq, unsigned int key);
node pop(priorityQueue *pq);
node peek(priorityQueue *pq);
int isEmpty (priorityQueue *pq);
void freeQueue(priorityQueue *pq);
int testQueue();
int size (priorityQueue *pq) ;

#endif
