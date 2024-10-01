#include "my_tar.h"

char* my_strcpy(char* src, char* dest){

    int index = 0;
    int index_dest = 0;
    printf("HELLO\n");

    // printf("src = %s\n", src);

    while (src[index] != 0){
        
        printf("index = %d src[index] = %c\n", index, src[index]);
        dest[index_dest] = src[index];
        index  += 1;
        index_dest += 1;
    }
    
    printf("patat_2\n");

    dest[index_dest] = 0;
    
    printf("final dest = %s\n", dest);
    return dest;
}