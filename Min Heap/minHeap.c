#include "minHeap.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) (x - 1) / 2

minHeap initMinHeap(int capacity) {
    minHeap hp ;
    hp.next_id = 0;
    if (capacity <= 0){
      printf("Capacity can't be <=0 initializing heap with capacity=10");
      capacity = 10;
    }
    hp.capacity = capacity ;
    hp.size = 0 ;
    hp.elem = (node*)malloc(capacity * sizeof(node));
    return hp ;
}

void pushHeap(minHeap *hp, int key) {
    // allocating space
    if(hp->size==hp->capacity) {
        printf("realloc the heap!\n");
        hp->capacity *= 2 ;
        hp->elem = (node*)realloc(hp->elem, (hp->capacity) * sizeof(node)) ;
    }

    // initializing the node with value
    node nd ;
    nd.key = key ;
    nd.id = (hp->next_id)++;
    printf("push node key: %d, id: %d\n", nd.key, nd.id) ;

    // Positioning the node at the right position in the min heap
    int i = (hp->size)++ ;
    while(i && nd.key < hp->elem[PARENT(i)].key) {
        hp->elem[i] = hp->elem[PARENT(i)] ;
        i = PARENT(i) ;
    }
    hp->elem[i] = nd ;
}

void swap(node *n1, node *n2) {
    node temp = *n1 ;
    *n1 = *n2 ;
    *n2 = temp ;
}

void heapify(minHeap *hp, int i) {
    int smallest = (LCHILD(i) < hp->size && hp->elem[LCHILD(i)].key < hp->elem[i].key) ? LCHILD(i) : i ;
    if(RCHILD(i) < hp->size && hp->elem[RCHILD(i)].key < hp->elem[smallest].key) {
        smallest = RCHILD(i) ;
    }
    if(smallest != i) {
        swap(&(hp->elem[i]), &(hp->elem[smallest])) ;
        heapify(hp, smallest) ;
    }
}

node popHeap(minHeap *hp) {
    node nd;
    if(hp->size) {
        nd=hp->elem[0];
        printf("pop node key: %d, id: %d\n", hp->elem[0].key, hp->elem[0].id) ;
        hp->elem[0] = hp->elem[--(hp->size)] ;
        hp->elem = (node*)realloc(hp->elem, hp->size * sizeof(node)) ;
        heapify(hp, 0) ;
    } else {
        printf("Min Heap is empty!\n") ;
        free(hp->elem) ;
        nd.key = INT_MIN;
        nd.id = INT_MIN;
    }
    return nd;
}

int isHeapEmpty(minHeap *hp){
  return hp->size ;
}

node peekHeap(minHeap *hp) {
  node nd;
  if(hp->size) {
      nd=hp->elem[0];
      printf("peek node key: %d, id: %d\n", hp->elem[0].key, hp->elem[0].id) ;
  } else {
      printf("Min Heap is empty!\n") ;
      nd.key = INT_MIN;
      nd.id = INT_MIN;
  }
  return nd;
}

int testHeap() {
    minHeap hp = initMinHeap(5) ;
    pushHeap(&hp, 1);
    pushHeap(&hp, 2);
    pushHeap(&hp, 8);
    peekHeap(&hp);
    pushHeap(&hp, 4);
    pushHeap(&hp, 3);
    peekHeap(&hp);
    pushHeap(&hp, 9);
    popHeap(&hp);
    popHeap(&hp);
    peekHeap(&hp);
    popHeap(&hp);
    popHeap(&hp);
    popHeap(&hp);
    popHeap(&hp);
    popHeap(&hp);
    return 0;
}
