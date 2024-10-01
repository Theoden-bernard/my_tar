#include "my_tar.h"

/*
cette fonction initialise tout la variable a 0;
*/

void my_memset(void* s, int c, size_t n){

    int index = 0;
printf("potate\n");
    char *string = (char *) s;
printf("cuillere\n");
    while(index < (int) n){
// printf("frite\n");
        string[index] = c;
// printf("patate %d\n", index);
        index += 1;
    }
}