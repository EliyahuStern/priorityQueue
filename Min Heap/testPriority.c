#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "priorityQueue.h"
#include "read.h"
#define LINE 29
#define NUM_OF_NODES 500
#define NUM_OF_LINES NUM_OF_NODES*2
#define PUSH 1
#define PEEK 0
#define POP -1

//function to make an action on the priority queue and prints the data into a given string//
void printToStringQueue (char** string, int action, int* id, priorityQueue* pq, int key){
  node nd;

  //write new size to the string, pedding with zeroes
  sprintf(*string, "%06d", action+size(pq)) ;
  *string += 6 ;
  **string = ' ' ;
  *string += 1 ;

  switch(action){
    case PUSH :
      //write PUSH into the string
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

      //initializing nd
      nd.key = key ;
      nd.id = (*id)++ ;

      //push to priority queue
      //printf("push: ");
      push(pq, key) ;
    break ;

    case POP:
      //write POP into the string
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
      //printf("pop : ") ;
      nd = pop(pq) ;
    break ;

    case PEEK :
      //write PEEK into the string
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
      //printf("peek: ");
      nd = peek(pq) ;
    break ;
  }

  //write the key to hex string, pedding with zeroes
  sprintf(*string, "%09x", nd.key) ;
  *string += 9 ;
  **string = ' ' ;
  (*string)++ ;
  **string = ' ' ;
  (*string)++ ;

  //warite the id to hex string, pedding with zeroes
  sprintf(*string, "%05x", nd.id) ;

  //next line
  *string += 5 ;
  **string = '\n' ;
  (*string)++ ;
  //printf("key: %d\tid: %d\n", nd.key, nd.id) ;
}

//function to write a string into the name file//
int writeToFileQueue(char* string, char* name) {
  //open the file
  FILE *f = fopen(name, "w");

  if (f == NULL){
    printf("Error opening file!\n");
    return 1;
  }
  //write string into the file
  fprintf(f, "%s", string);
  //close the file
  fclose(f);
  return 0;
}

//function to write a test into text file-"theTest.txt"//
int writeTestToTextQueue( char* theTest) {
  //initializing things
  char* string = (char*) malloc (sizeof(char) * LINE * NUM_OF_LINES) ;
  char* start = string ;
  int id = 1 ;
  int action ;
  int key ;
  priorityQueue pq = initPriorityQueue() ;
  srand((unsigned)time(NULL));   // should only be called once

  //loop that makes the test
  int i = 0 ;
  while(id <= NUM_OF_NODES){
    if(i%6==5) action = -1 ;
    else{
      action = 1 ;
      // generate random unsigned int for key
      key = rand();
      //key += rand();
    }
    //make the action and insert into the test string
    printToStringQueue(&string, action, &id, &pq, key) ;
    //printf("i=%d\n", i);
    i++ ;
  }

  //empty the priority Queue
  action = -1 ;
  while(!isEmpty(&pq)){
    printToStringQueue(&string, action, &id, &pq, key) ;
  }

  //close the string
  string-- ;
  string[0] = '\0' ;
  //write the test string into a file
  writeToFileQueue(start, theTest) ;
  //freeQueue(&pq) ;
  return 0;
}

//function to check "theTest.txt" file//
void testTheTextQueue(char* name, char* result){
  //initializing things
  read r = ReadFile(name) ;
  priorityQueue pq = initPriorityQueue();
  char* writeString = (char*) malloc (sizeof(char) * r.length ) ;
  char* start = writeString ;
  char* readString = r.text ;
  int action ;

  //read a line from test text and write the results in the writeString
   for(int i = 0 ; i <= r.length/LINE ; i++){
     //reading the size of the prioirity queue(after the action) from text
     int nextSize = (int)strtol(readString, NULL, 10) ;
     //initializing the action by the size
     action = nextSize - size(&pq) ;
     //reading key from text
     readString += 12 ;
     int key = (int)strtol(readString, NULL, 16) ;
     //reading id from text
     readString += 11 ;
     int id = (int)strtol(readString, NULL, 16) ;
     //do action on the priority queue and print it to the writeString
     printToStringQueue(&writeString, action, &id, &pq, key) ;
     //next line
     readString+=6 ;
   }

   //close the writeString
   writeString-- ;
   writeString[0] = '\0' ;
   //write the writeString into file "result.txt"
   writeToFileQueue(start, result) ;
}

int main(int argc, char const *argv[]) {
  char* theTest ="theTestQueue.txt";
  char* result= "resultQueue.txt" ;
  writeTestToTextQueue(theTest);
  //testTheTextQueue(theTest, result) ;
  printf("done with test priority\n") ;
  return 0 ;
}
