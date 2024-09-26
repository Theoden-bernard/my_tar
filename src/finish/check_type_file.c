#include "my_tar.h"

/*cette fonction regarde qu'elle type de fichier c'est .c .tar ....*/
int check_type_file(char* file, char* type){

    int index_file = 0;
    int index_type = 0;
    int size = my_strlen(type);
    int compt = 0;

    printf("tutu\n");
    while (file[index_file] != 0){

        printf("index_file[%c] = %d - %p\n", file[index_file], index_file, &(file[index_file]));
        if(file[index_file] == type[index_type]){
            
            printf("flag_1\n");
            compt += 1;
            index_type += 1;

        }else{
            
            printf("flag_2\n");
            compt = 0;
            index_type = 0;
        }
        printf("%d jsp quoi\n", file[index_file]);
        index_file += 1;
        printf("%d jsp quoi\n", file[index_file]);
    }
    printf("tata\n");
    if (size == compt){

        return 1;
    }else{
        
        return 0;
    }
    printf("toto\n");
}