#include "my_tar.h"

char* my_realloc(char* str, int size){

    // printf("size_2 = %d", size);
    char* new_str = malloc(sizeof(char) * size);
    my_strcpy(str , new_str);

    free(str);
    return new_str;
}