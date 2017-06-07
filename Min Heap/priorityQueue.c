#include "priorityQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define AVARAGE_CAPACITY 20000
#define HEAPS 50

priorityQueue* initPriorityQueue(){
  priorityQueue* pq = (priorityQueue*)malloc(sizeof(priorityQueue)) ;
  pq->id = 1 ;
  pq->size = 0 ;
  pq->indexes = initMaxHeap(HEAPS, -1) ;
  pq->ranges = (maxHeap**)malloc(HEAPS * sizeof(node)) ;
  for( int i = 0 ; i < HEAPS ; i++ ){
    pq->ranges[i]=initMaxHeap(AVARAGE_CAPACITY , i) ;
  }
  return pq ;
}

int getRangeIndex (unsigned int key){
  //unsigned int max = INT_MAX ;
  //max += INT_MAX ;
  if(key) return key / (INT_MAX / HEAPS) ;
  else return 0 ;
}

void push(priorityQueue *pq, unsigned int key){
  int  index = getRangeIndex (key);

  //if the spesific range heap is empty:
  if(isHeapEmpty((pq->ranges[index]))){
    //push the right index to the index heap
    pushHeap((pq->indexes), index, -1) ;
  }
  //push the key to the right range heap
  pushHeap((pq->ranges[index]), key, (pq->id)++) ;
  //printf("push: heap: %d\tsize: %d\tkey: %d,\tid: %u\n",index,heapSize(&(pq->ranges[index])), key, pq->id);
  (pq->size)++;
}

node* pop(priorityQueue *pq){
  node* nd = (node*)malloc(sizeof(node));
  //if there are nodes in pq
  if(!isEmpty(pq)){
    int index = peekHeap(pq->indexes)->key ;
    nd = popHeap(pq->ranges[index]) ;
    //printf("pop:  heap: %d\tsize: %d\tkey: %d,\tid: %u\n",index,heapSize(&(pq->ranges[index])), nd.key, nd.id);
    if(isHeapEmpty(pq->ranges[peekHeap(pq->indexes)->key])){
      popHeap(pq->indexes) ;
    }
    (pq->size)--;
    //printf("pop: \tkey: %d,\tid:%u\n", nd.key, nd.id);
  }else{
    printf("(pop)Priority Queue is empty!\n") ;
    nd->key = 0 ;
    nd->id = INT_MIN ;
  }
  return nd ;
}

node* peek(priorityQueue *pq){
  node* nd = (node*)malloc(sizeof(node)) ;
  if(!isHeapEmpty(pq->indexes)){
    nd = peekHeap(pq->ranges[peekHeap(pq->indexes)->key]) ;
    //printf("peek:\tkey: %d,\tid:%u\n", nd.key, nd.id) ;
  }else{
    printf("(peek)Priority Queue is empty!\n") ;
    nd->key = 0 ;
    nd->id = INT_MIN ;
  }
  return nd ;
}

int isEmpty (priorityQueue *pq){
  return !pq->size;
}

int size (priorityQueue *pq){
  return pq->size;
}

void freeQueue(priorityQueue *pq){
  while(!isHeapEmpty(pq->indexes)){
    node* nd = popHeap(pq->indexes) ;
    freeHeap(pq->ranges[nd->key]);
  }
  free(pq->ranges);
}

int testQueue() {
    printf("priorityQueue test:\n");
    int array[] = {15, 2789456, 5678245, 9464646, 76542456, 75, 34563087, 456453663, 95634905, 456348765};
    int size = 10 ;
    priorityQueue* pq=initPriorityQueue();
    for (int i = 0 ; i < size ; i++){
        push(pq, array[i]);
        if(i%3==0)pop(pq);
        if(i%4==0&&i!=0) peek(pq);
    }
    while(!isEmpty(pq)) {peek(pq);
      pop(pq);}
      pop(pq);
      peek(pq);
    return 0;
}
