#ifndef MIN_HEAP
#define MIN_HEAP

typedef struct node {
    int key ;
    int id;
} node ;

typedef struct minHeap {
    int num_of_heap ;
    int next_id ;
    int size ;
    int capacity;
    node *elem ;
} minHeap ;

minHeap initMinHeap(int capacity, int num);
void pushHeap(minHeap *hp, int key);
node popHeap(minHeap *hp);
node peekHeap(minHeap *hp);
int isHeapEmpty(minHeap *hp);

int testHeap();

#endif
