#include "my_tar.h"

//le but est de faire en sorte que cette fonction marche

char* convertiseur_base(int base_10, int base, int size){

    int index = size;
    // char* result_base = malloc(sizeof(char) * 1);
    char* storage = malloc(sizeof(char) * (size + 1));
    int result = 0;
    int last_number = 0;

    // printf("before base 10 = %d\n", base_10);

    my_bzero(storage, index);
    
    storage[index] = '\0';

    index -= 1;

    printf("patate\n");

    while (base_10 != 0)
    {

        last_number = (base_10 % base); // je chope le dernier chiffre

        result = (base_10 - (base_10 % base)) / base/* % base*/; 
        if (last_number > 9){

            storage[index] = last_number + 'A' - 9;
        }else{
            storage[index] = last_number + '0';
        }
    
        base_10 = result;
        index -= 1;   
    }

    //storage = reverse_string(storage, size);

    return storage;
}