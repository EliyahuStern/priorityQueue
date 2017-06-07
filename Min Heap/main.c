#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "priorityQueue.h"
#include "read.h"


int main1(int argc, char const *argv[]) {
  priorityQueue pq = initPriorityQueue();
  node nd ;
  int flag = 0 ;
  int size = 0 ;
  char* string = ReadFile("randoms.txt") ;
  int i = 0 ;
   while(i < 10000){
    int num = (int)strtol(string, NULL, 10) ;
    int action = num - size ;
    size += action ;
    string+=11 ;
    int key = (int)strtol(string, NULL, 16) ;
    string+=10 ;
    int id = (int)strtol(string, NULL, 16) ;
    switch(action){
      case -1 :
        printf("POP:\tkey: %d, \tid:%d\n", key, id) ;
        nd = pop(&pq) ;
        if(nd.key != key) flag = 1 ;
        break ;
      case 0 :
        printf("PEEK:\tkey: %d, \tid:%d\n", key, id) ;
        nd = peek(&pq) ;
        if(nd.key != key) flag = 1 ;
        break ;
      case 1 :
        printf("PUSH:\tkey: %d, \tid:%d\n", key, id) ;
        push(&pq, key) ;
        break ;
      default :
        printf("here!") ;
    }
    //printf("size= %d\t pq size= %d\t num= %d\n", size, pq.size, num) ;
    string+=9 ;
    if(flag) {
      break ;
      printf("break in i = %d", i) ;
    }
    i++ ;
   }
  return 0;
}
