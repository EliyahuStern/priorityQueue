#ifndef MIN_HEAP
#define MIN_HEAP

typedef struct node {
    int key ;
    int id;
} node ;

typedef struct minHeap {
    int next_id ;
    int size ;
    int capacity;
    node *elem ;
} minHeap ;

minHeap initMinHeap(int capacity);
void pushHeap(minHeap *hp, int key);
node popHeap(minHeap *hp);
node peekHeap(minHeap *hp);
int isHeapEmpty(minHeap *hp);

int testHeap();

#endif
