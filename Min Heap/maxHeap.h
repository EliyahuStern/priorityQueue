#ifndef MAX_HEAP
#define MAX_HEAP

typedef struct node {
    unsigned int key ;
    int id;
} node ;

typedef struct maxHeap {
    //lastPoped value would be 0 if last action wasn't popHeap
    int lastPoped ;
    int num_of_heap ;
    int size ;
    int capacity ;
    node *elem ;
} maxHeap ;

maxHeap initMaxHeap(int capacity, int num_of_heap);
void pushHeap(maxHeap *hp, unsigned int key, int id);
node popHeap(maxHeap *hp);
node peekHeap(maxHeap *hp);
int isHeapEmpty(maxHeap *hp);
void freeHeap (maxHeap *hp);
int heapSize (maxHeap *hp) ;
int testHeap();

#endif
