#include "my_tar.h"

int int_len(int integer){

    int index = 0;

    while (integer != 0)
    {   
        integer = integer / 10;
        index += 1;
    }
    
    return index;
}