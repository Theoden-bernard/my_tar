#include "my_tar.h"

char* my_strcpy(char* src, char* dest){

    int index = 0;
    int index_dest = 0;

    // printf("src = %s\n", src);

    while (src[index] != 0){
    
        dest[index_dest] = src[index];
        index  += 1;
        index_dest += 1;
    }

    dest[index_dest] = 0;
    
    return dest;
}