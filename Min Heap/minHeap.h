#ifndef MIN_HEAP
#define MIN_HEAP

typedef struct node {
    int key ;
    unsigned int id;
} node ;

typedef struct minHeap {
    //lastPoped value would be 0 if last action wasn't popHeap
    int lastPoped ;
    int num_of_heap ;
    int size ;
    int capacity ;
    node *elem ;
} minHeap ;

minHeap initMinHeap(int capacity, int num);
void pushHeap(minHeap *hp, int key, unsigned int id);
node popHeap(minHeap *hp);
node peekHeap(minHeap *hp);
int isHeapEmpty(minHeap *hp);
void freeHeap (minHeap *hp);
int testHeap();

#endif
