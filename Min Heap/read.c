#include <stdio.h>
#include <stdlib.h>
#include "read.h"
char* ReadFile(char *filename)
{
   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(filename, "r");

   if (handler)
   {
       // Seek the last byte of the file
       fseek(handler, 0, SEEK_END);
       // Offset from the first to the last byte, or in other words, filesize
       string_size = ftell(handler);
       // go back to the start of the file
       rewind(handler);

       // Allocate a string that can hold it all
       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

       // Read it all in one operation
       read_size = fread(buffer, sizeof(char), string_size, handler);

       // fread doesn't set it so put a \0 in the last position
       // and buffer is now officially a string
       buffer[string_size] = '\0';

       if (string_size != read_size)
       {
           // Something went wrong, throw away the memory and set
           // the buffer to NULL
           free(buffer);
           buffer = NULL;
       }

       // Always remember to close the file.
       fclose(handler);
    }

    return buffer;
}

int readf()
{
    char* string = ReadFile("randoms.txt");
    if (string)
    {
        puts(string);
        free(string);
    }
    return 0;
}

int testRead() {
  int size = 0;
  char* string = ReadFile("randoms.txt") ;
  int i = 0 ;
   while(i < 22){
    int num = (int)strtol(string, NULL, 16) ;
    int action = num-size ;
    size = size + action ;
    string+=11 ;
    int key = (int)strtol(string, NULL, 16) ;
    string+=10 ;
    int id = (int)strtol(string, NULL, 16) ;
    switch(action){
      case -1 :
        printf("POP: key: %d, id:%d\n", key, id) ;
        break ;
      case 0 :
        printf("PEEK:key: %d, id:%d\n", key, id) ;
        break ;
      case 1 :
        printf("PUSH:key: %d, id:%d\n", key, id) ;
        break ;
    }
    string+=9 ;
    i++ ;
   }
  return 0;
}
