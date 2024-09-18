#include "my_tar.h"

char* my_bzero(char* string, int size){

    int index = 0;

    while (index < size){

        string[index] = 48;
        index += 1;
    }

    printf("string %s\n\n", string);

    return string;
}