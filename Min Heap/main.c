#include <stdio.h>
#include <stdlib.h>
#include "priorityQueue.h"
#include "read.h"

int main(int argc, char const *argv[]) {
  priorityQueue pq=initPriorityQueue();
  int size = 0;
  char* string = ReadFile("randoms.txt") ;
  int i = 0 ;
   while(i < 10){
    int num = (int)strtol(string, NULL, 16) ;
    int action = num-size ;
    size = size + action ;
    string+=11 ;
    int key = (int)strtol(string, NULL, 16) ;
    string+=10 ;
    int id = (int)strtol(string, NULL, 16) ;
    switch(action){
      case -1 :
        printf("POP:\tkey: %d, \tid:%d\n", key, id) ;
        pop(&pq) ;
        break ;
      case 0 :
        printf("PEEK:\tkey: %d, \tid:%d\n", key, id) ;
        peek(&pq) ;
        break ;
      case 1 :
        printf("PUSH:\tkey: %d, \tid:%d\n", key, id) ;
        push(&pq, key) ;
        break ;
    }
    string+=9 ;
    i++ ;
   }
  return 0;
}
