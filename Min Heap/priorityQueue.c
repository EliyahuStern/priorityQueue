#include "priorityQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define AVARAGE_CAPACITY 100000
#define HEAPS 1000

priorityQueue initPriorityQueue(){
  priorityQueue pq ;
  pq.size=0 ;
  pq.indexes = initMinHeap(HEAPS) ;
  pq.ranges = (minHeap*)malloc(HEAPS * sizeof(node)) ;
  for( int i = 0 ; i < HEAPS ; i++ ){
    pq.ranges[i]=initMinHeap(AVARAGE_CAPACITY * 2 / HEAPS) ;
  }
  return pq ;
}

void push(priorityQueue *pq, int key){
    if(!isHeapEmpty(&(pq->ranges[key ? INT_MAX / key : 0]))){
    pushHeap(&(pq->indexes), key ? INT_MAX / key : 0) ;
  }
  pushHeap(&(pq->ranges[key ? INT_MAX / key : 0]), 0) ;
  (pq->size)++;
}

node pop(priorityQueue *pq){
  if(isHeapEmpty(&(pq->indexes)) != 0){
    node nd = popHeap(&(pq->ranges[peekHeap(&(pq->indexes)).key])) ;
    if(isHeapEmpty(&(pq->ranges[peekHeap(&(pq->indexes)).key])) == 0){
      popHeap(&(pq->indexes)) ;
    }
    (pq->size)--;
    return nd ;
  }else{
    printf("Priority Queue is empty!\n") ;
    return peekHeap(&(pq->indexes)) ;
  }
}

node peek(priorityQueue *pq){
  if(isHeapEmpty(&(pq->indexes)) != 0){
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
    int array[] = {0, 77777777, 15555555, 646464, 76542456, 75, 34563, 45645363, 456345, 456345};
    int size = 10 ;
    priorityQueue pq=initPriorityQueue();
    for (int i = 0 ; i < size ; i++){
        push(&pq, array[i]);
        if(i%2==0) peek(&pq);
        if(i%3==0) pop(&pq);
    }
    while(isEmpty(&pq) != 0) pop(&pq);
    return 0;
}
