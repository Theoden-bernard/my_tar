#include "my_tar.h"

/*
cette fonction initialise tout la variable a 0;
*/

void my_memset(void* s, int c, size_t n){

    size_t index = 0;

    char *string = (char *) s;

    while(index != n){

        string[index] = c;

        index += 1;
    }
}