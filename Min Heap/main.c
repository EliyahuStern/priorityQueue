#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "priorityQueue.h"
#include "maxHeap.h"
#include "read.h"
#define LINE 31
#define NUM_OF_LINES 10
#define PUSH 1
#define PEEK 0
#define POP -1

void printToString1 (char** string, int action, int* id, priorityQueue* pq, int key){
  node nd;

  //write action to the string, pedding with zeroes
  sprintf(*string, "%05d", action+size(pq)) ;
  *string += 5 ;
  **string = ' ' ;
  *string += 1 ;

  switch(action){
    case PUSH :
      **string = 'P' ;
      (*string)++ ;
      **string = 'U' ;
      (*string)++ ;
      **string = 'S' ;
      (*string)++ ; ;
      **string = 'H' ;
      (*string)++ ;
      **string = ' ' ;
      (*string)++ ;

      nd.key = key ;
      nd.id = (*id)++ ;

      //push to priority queue
      push(pq, key) ;
      break ;

    case POP:
    **string = 'P' ;
    (*string)++ ;
    **string = 'O' ;
    (*string)++ ;
    **string = 'P' ;
    (*string)++ ; ;
    **string = ' ' ;
    (*string)++ ;
    **string = ' ' ;
    (*string)++ ;

      //pop prom priority queue
      nd = pop(pq) ;
      break ;

    case PEEK :
    **string = 'P' ;
    (*string)++ ;
    **string = 'E' ;
    (*string)++ ;
    **string = 'E' ;
    (*string)++ ; ;
    **string = 'K' ;
    (*string)++ ;
    **string = ' ' ;
    (*string)++ ;

      //peek prom priority queue
      nd = peek(pq) ;
      break ;
  }

  //write the key to hex string, pedding with zeroes
  sprintf(*string, "%08x", nd.key);
  *string += 8 ;
  **string = ' ' ;
  (*string)++ ;
  **string = ' ' ;
  (*string)++ ;

  //warite the id to hex string, pedding with zeroes
  sprintf(*string, "%08x", nd.id);

  *string += 8 ;
  **string = '\n' ;
  (*string)++ ;
}

int writeToFile1(char* string) {
  FILE *f = fopen("test.txt", "w");
  if (f == NULL){
    printf("Error opening file!\n");
    return 1;
  }

  fprintf(f, "%s", string);
  fclose(f);
  return 0;
}

int readLoop1(int argc, char const *argv[]) {
  priorityQueue pq = initPriorityQueue();
  node nd ;
  int flag = 0 ;
  int size = 0 ;
  read r = ReadFile("randoms.txt") ;
  char* string = r.text ;
  int i = 0 ;
   while(i < NUM_OF_LINES){
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

void testTheText1(){
  priorityQueue pq = initPriorityQueue();
  char* writeString = (char*) malloc (sizeof(char) * LINE * NUM_OF_LINES) ;
  char* start = writeString ;
  read r = ReadFile("randoms.txt") ;
  char* readString = r.text ;
  int i = 0 ;
  int action ;
   while(i < NUM_OF_LINES){
    int num = (int)strtol(readString, NULL, 10) ;
    action = num - size(&pq) ;
    readString+=11 ;
    int key = (int)strtol(readString, NULL, 16) ;
    readString+=10 ;
    int id = (int)strtol(readString, NULL, 16) ;
    printToString1(&writeString, action, &id, &pq, key) ;
    readString+=9 ;
    i++ ;
   }
   writeString-- ;
   writeString[0] = '\0' ;
   printf("thats it!\n");
   puts(start);
   writeToFile1(start) ;
}

int writeTestToText1() {
  char* string = (char*) malloc (sizeof(char) * LINE * NUM_OF_LINES) ;
  char* start = string ;
  int id = 1 ;
  int action ;
  int key ;
  priorityQueue pq = initPriorityQueue() ;
  srand((unsigned)time(NULL));   // should only be called once

  for (int i = 0 ; i < NUM_OF_LINES ; i++){
    if(i%2==1) action = -1 ;
    else{
      action = 1 ;
      // generate random unsigned int for key
      key = rand();
      //key += rand();
    }
    printToString1(&string, action, &id, &pq, key) ;
  }

  string-- ;
  string[0] = '\0' ;
  writeToFile1(start) ;
  //freeQueue(&pq) ;
  return 0;
}

int main1(int argc, char const *argv[]) {
  testTheText1();
  return 0;
}
