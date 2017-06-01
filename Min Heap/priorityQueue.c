#include "minHeap.h"
#include "priorityQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define AVARAGE_CAPACITY 100000
#define HEAPS 1000

priorityQueue initPriorityQueue(){
  priorityQueue pq ;
  pq.size=0 ;
  pq.indexes = initMinHeap(HEAPS, -1) ;
  pq.ranges = (minHeap*)malloc(HEAPS * sizeof(node)) ;
  for( int i = 0 ; i < HEAPS ; i++ ){
    pq.ranges[i]=initMinHeap((AVARAGE_CAPACITY * 2 / HEAPS), i) ;
  }
  //printf("17\n");
  return pq ;
}

void push(priorityQueue *pq, int key){
  printf("push: %d\n", key);
    //if the spesific range heap is empty:
    int  index ;
    if(!key) index = 0 ;
    else index = key / (INT_MAX / HEAPS);
    if(!isHeapEmpty(&(pq->ranges[index]))){
    //push the right index to the index heap
    pushHeap(&(pq->indexes), index) ;
  }
  //push the key to the right range heap
  pushHeap(&(pq->ranges[index]), key) ;
  (pq->size)++;
}

node pop(priorityQueue *pq){
  //if thre are nodes in
  if(pq->size != 0){
    int index = peekHeap(&(pq->indexes)).key ;
    node nd = popHeap(&(pq->ranges[index])) ;
    if(isHeapEmpty(&(pq->ranges[peekHeap(&(pq->indexes)).key])) == 0){
      popHeap(&(pq->indexes)) ;
    }
    (pq->size)--;
    printf("pop: %d\n", nd.key);
    return nd ;
  }else{
    printf("Priority Queue is empty!\n") ;
    return peekHeap(&(pq->indexes)) ;
  }
}

node peek(priorityQueue *pq){
  if(isHeapEmpty(&(pq->indexes)) != 0){
    printf("peek: %d\n", peekHeap(&(pq->ranges[peekHeap(&(pq->indexes)).key])).key) ;
    return peekHeap(&(pq->ranges[peekHeap(&(pq->indexes)).key])) ;
  }else{
    printf("Priority Queue is empty!\n") ;
    return peekHeap(&(pq->indexes)) ;
  }
}

int isEmpty (priorityQueue *pq){
  return pq->size;
}

int testQueue() {
    printf("priorityQueue test:\n");
    int array[] = {15, 2789456, 5678245, 9464646, 76542456, 75, 34563087, 456453663, 95634905, 456348765};
    int size = 10 ;
    priorityQueue pq=initPriorityQueue();
    for (int i = 0 ; i < size ; i++){
        push(&pq, array[i]);
    }
    while(isEmpty(&pq)) pop(&pq);
    return 0;
}
