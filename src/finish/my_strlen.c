#include "my_tar.h"

int my_strlen(char* string){

    int index = 0;

    if (string == NULL){
        
        return index;
    }

    while (string[index] != 0){
        
        index += 1;
    }

    return index + 1;
}