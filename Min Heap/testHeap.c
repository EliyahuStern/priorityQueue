#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maxHeap.h"
#include "read.h"
#define LINE 29
#define NUM_OF_NODES 100000
#define NUM_OF_LINES NUM_OF_NODES*2
#define PUSH 1
#define PEEK 0
#define POP -1

//function to make an action on the maxHeap and prints the data into a given string//
void printToStringHeap (char** string, int action, int* id, maxHeap* hp, int key){
  node nd;

  //write new size to the string, pedding with zeroes
  sprintf(*string, "%06d", action+heapSize(hp)) ;
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

      //push to maxHeap
      printf("push: ");
      pushHeap(hp, nd.key, nd.id) ;
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

      //pop prom maxHeap
      printf("pop : ") ;
      nd = popHeap(hp) ;
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

      //peek prom maxHeap
      printf("peek: ");
      nd = peekHeap(hp) ;
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
  printf("key: %d\tid: %d\n", nd.key, nd.id) ;
}

//function to write a string into the name file//
int writeToFileHeap(char* string, char* name) {
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
int writeTestToTextHeap( char* theTest) {
  //initializing things
  char* string = (char*) malloc (sizeof(char) * LINE * NUM_OF_LINES) ;
  char* start = string ;
  int id = 1 ;
  int action ;
  int key ;
  maxHeap hp = initMaxHeap(NUM_OF_NODES, 0) ;
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
    printToStringHeap(&string, action, &id, &hp, key) ;
    printf("i=%d\n", i);
    i++ ;
  }

  //empty the heap
  action = -1 ;
  while(!isHeapEmpty(&hp)){
    printToStringHeap(&string, action, &id, &hp, key) ;
  }

  //close the string
  string-- ;
  string[0] = '\0' ;
  //write the test string into a file
  writeToFileHeap(start, theTest) ;
  //freeQueue(&pq) ;
  return 0;
}

//function to check "theTest.txt" file//
void testTheTextHeap(char* name, char* result){
  //initializing things
  read r = ReadFile(name) ;
  maxHeap hp = initMaxHeap(NUM_OF_NODES, 0);
  char* writeString = (char*) malloc (sizeof(char) * r.length ) ;
  char* start = writeString ;
  char* readString = r.text ;
  int action ;

  //read a line from test text and write the results in the writeString
   for(int i = 0 ; i <= r.length/LINE ; i++){
     //reading the size of the prioirity queue(after the action) from text
     int nextSize = (int)strtol(readString, NULL, 10) ;
     //initializing the action by the size
     action = nextSize - heapSize(&hp) ;
     //reading key from text
     readString += 12 ;
     int key = (int)strtol(readString, NULL, 16) ;
     //reading id from text
     readString += 11 ;
     int id = (int)strtol(readString, NULL, 16) ;
     //do action on the maxHeap and print it to the writeString
     printToStringHeap(&writeString, action, &id, &hp, key) ;
     //next line
     readString+=6 ;
   }

   //close the writeString
   writeString-- ;
   writeString[0] = '\0' ;
   //write the writeString into file "result.txt"
   writeToFileHeap(start, result) ;
}

int main(int argc, char const *argv[]) {
  char* theTest ="theTestHeap.txt";
  char* result= "resultHeap.txt" ;
  writeTestToTextHeap(theTest);
  testTheTextHeap(theTest, result) ;
  return 0 ;
}
