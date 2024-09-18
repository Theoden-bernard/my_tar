//cette fonction permet de calculer le nombre de mot dans un char**
#include "my_tar.h"

int wordlen(char** word){

    int index = 0;
    printf("word[index] = %s\n", word[index]);

    while (word[index] != 0){
        index += 1;
    }

    printf("wordlen == %d\n", index);
    return index;
}