#include "my_tar.h"

/*
fonction qui transforme un int en char
*/

char* int_to_char(int integer){

    int zero_in_char = 48;
    int index = 0;
    int size = int_len(integer) - 1; 
    
    char* str = malloc(sizeof(char) * size);

    while (integer != 0)
    {
        
        index = 0;
        zero_in_char = 48;

        while(integer % 10 != index){

            zero_in_char += 1;
            index += 1;
        }

        str[size] = zero_in_char;
        
        size -= 1;

        integer = integer / 10;
    }

    return str;
}