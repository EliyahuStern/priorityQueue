#include "minHeap.h"
#include "priorityQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define AVARAGE_CAPACITY 100000
#define HEAPS 1000

priorityQueue initPriorityQueue(){
  priorityQueue pq ;
  pq.id = 0 ;
  pq.size = 0 ;
  pq.indexes = initMinHeap(HEAPS, -1) ;
  pq.ranges = (minHeap*)malloc(HEAPS * sizeof(node)) ;
  for( int i = 0 ; i < HEAPS ; i++ ){
    pq.ranges[i]=initMinHeap((AVARAGE_CAPACITY * 2 / HEAPS), i) ;
  }
  //printf("17\n");
  return pq ;
}

int getRangeIndex (int key){
  if(key) return key / (INT_MAX / HEAPS) ;
  else return 0 ;
}

void push(priorityQueue *pq, int key){
  printf("push: key: %d, id: %u\n", key, pq->id);
    int  index = getRangeIndex (key);
    //if the spesific range heap is empty:
    if(isHeapEmpty(&(pq->ranges[index]))){
    //push the right index to the index heap
    pushHeap(&(pq->indexes), index, -1) ;
  }
  //push the key to the right range heap
  pushHeap(&(pq->ranges[index]), key, (pq->id)++) ;
  (pq->size)++;
}

node pop(priorityQueue *pq){
  //if there are nodes in
  if(!isEmpty(pq)){
    int index = peekHeap(&(pq->indexes)).key ;
    node nd = popHeap(&(pq->ranges[index])) ;
    if(isHeapEmpty(&(pq->ranges[peekHeap(&(pq->indexes)).key]))){
      popHeap(&(pq->indexes)) ;
    }
    (pq->size)--;
    printf("pop:  key: %d, id: %u\n", nd.key, nd.id);
    return nd ;
  }else{
    printf("Priority Queue is empty!\n") ;
    return peekHeap(&(pq->indexes)) ;
  }
}

node peek(priorityQueue *pq){
  if(!isHeapEmpty(&(pq->indexes))){
    node nd = peekHeap(&(pq->ranges[peekHeap(&(pq->indexes)).key])) ;
    printf("peek: key: %d, id: %u\n", nd.key, nd.id) ;
    return nd ;
  }else{
    printf("Priority Queue is empty!\n") ;
    return peekHeap(&(pq->indexes)) ;
  }
}

int isEmpty (priorityQueue *pq){
  return !pq->size;
}

void freeQueue(priorityQueue *pq){
  while(!isHeapEmpty(&(pq->indexes))){
    node nd = popHeap(&(pq->indexes)) ;
    freeHeap(&(pq->ranges[nd.key]));
  }
  free(pq->ranges);
}

int testQueue() {
    printf("priorityQueue test:\n");
    int array[] = {15, 2789456, 5678245, 9464646, 76542456, 75, 34563087, 456453663, 95634905, 456348765};
    int size = 10 ;
    priorityQueue pq=initPriorityQueue();
    for (int i = 0 ; i < size ; i++){
        push(&pq, array[i]);
    }
    while(!isEmpty(&pq)) {peek(&pq); pop(&pq);}
    return 0;
}
