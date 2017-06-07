#include "minHeap.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) (x - 1) / 2

minHeap initMinHeap(int capacity, int num_of_heap) {
    minHeap hp ;
    hp.lastPoped = 0 ;
    hp.num_of_heap = num_of_heap ;
    if (capacity <= 0){
      printf("Capacity can't be <=0 initializing heap with capacity=10");
      capacity = 10;
    }
    hp.capacity = capacity ;
    hp.size = 0 ;
    hp.elem = (node*)malloc(capacity * sizeof(node));
    return hp ;
}

void swap(node *n1, node *n2) {
    node temp = *n1 ;
    *n1 = *n2 ;
    *n2 = temp ;
}

void heapify(minHeap *hp, int i) {
    int smallest = (LCHILD(i) < hp->size && hp->elem[LCHILD(i)].key > hp->elem[i].key) ? LCHILD(i) : i ;
    if(RCHILD(i) < hp->size && hp->elem[RCHILD(i)].key > hp->elem[smallest].key) {
        smallest = RCHILD(i) ;
    }
    if(smallest != i) {
        swap(&(hp->elem[i]), &(hp->elem[smallest])) ;
        heapify(hp, smallest) ;
    }
}

void pushHeap(minHeap *hp, int key, unsigned int id) {
  // initializing the node with value
  node nd;
  nd.key = key ;
  nd.id = id ;

  if (hp->lastPoped){
    hp->elem[0] = nd ;
    hp->lastPoped = 0;
    heapify(hp, 0) ;
  }else{
    // reallocating space
    if(hp->size == hp->capacity) {
        printf("realloc the %d heap!\n", hp->num_of_heap);
         hp->capacity *= 2 ;
        //(hp->elem) = (node*)realloc((hp->elem), (hp->capacity) * sizeof(node)) ;
        node* temp = (node*)malloc((hp->capacity) * sizeof(node));
        memcpy(temp, hp->elem, (hp->capacity/2)*sizeof(node)) ;
        //free(hp->elem) ;
        hp->elem = temp ;
    }
    // Positioning the node at the right position in the min heap
    int i = (hp->size)++ ;
    while(i && nd.key > hp->elem[PARENT(i)].key) {
        hp->elem[i] = hp->elem[PARENT(i)] ;
        //&(hp->elem[i]) == (char*)hp->elem + sizeof(*elem) * i)
        i = PARENT(i) ;
    }
    hp->elem[i] = nd ;
  }
  hp->lastPoped = 0;
}

void handleLastPoped (minHeap *hp){
    if(hp->size) --(hp->size);
    hp->elem[0] = hp->elem[hp->size] ;
    heapify(hp, 0) ;
}

node popHeap(minHeap *hp){
  node nd;
  if(hp->lastPoped) {
    handleLastPoped(hp) ;
  }
  if(hp->size) {
      nd=hp->elem[0];
  } else {
      printf("(pop)Min Heap %d is empty!\n", hp->num_of_heap) ;
      nd.key = INT_MIN;
      nd.id = INT_MIN;
  }
  hp->lastPoped = 1 ;
  return nd;
}

node peekHeap(minHeap *hp) {
  node nd;
  if(hp->lastPoped) {
    handleLastPoped(hp) ;
  }
  if(hp->size) {
      nd=hp->elem[0];
  }else {
      printf("(peek)Min Heap %d is empty!\n", hp->num_of_heap) ;
      nd.key = INT_MIN;
      nd.id = INT_MIN;
  }
  hp->lastPoped = 0 ;
  return nd;
}

int isHeapEmpty(minHeap *hp){
  if(hp->lastPoped)return !((hp->size)-1);
  return !(hp->size);
}

void freeHeap (minHeap *hp){
  free(hp->elem);
}

int testMinHeap() {
    minHeap hp = initMinHeap(5, -2) ;
    node nd ;
    int array[] = {2, 5, 3, 7, 4, 8, 6, 24, 77, 54};
    int size = 10 ;
    for(int i=0; i<size; i++){
      pushHeap(&hp, array[i], i);
      printf("push: key: %d, id: %u\n",array[i] , i) ;
      if(i%3==0){
        nd=popHeap(&hp);
        printf("pop: key: %d, id: %u\n", nd.key, nd.id) ;
      }
      if(i%4==0&&i!=0) {
        nd = peekHeap(&hp);
        printf("peek: key: %d, id: %u\n", nd.key, nd.id) ;
      }
    }
    while(!isHeapEmpty(&hp)) {
      nd=peekHeap(&hp);
      printf("peek: key: %d, id: %u\n", nd.key, nd.id) ;
      nd=popHeap(&hp);
      printf("pop: key: %d, id: %u\n", nd.key, nd.id) ;
    }
    nd=peekHeap(&hp);
    printf("peek: key: %d, id: %u\n", nd.key, nd.id) ;
    nd=popHeap(&hp);
    printf("pop: key: %d, id: %u\n", nd.key, nd.id) ;
    return 0;
}
