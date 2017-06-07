#ifndef READ
#define READ

typedef struct read {
    char* text ;
    int length ;
} read ;
read ReadFile(char *filename) ;

#endif
