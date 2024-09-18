#include "my_tar.h"

/*cette fonction regarde qu'elle type de fichier c'est .c .tar ....*/
int check_type_file(char* file, char* type){

    int index_file = 0;
    int index_type = 0;
    int size = my_strlen(type);
    int compt = 0;

    while (file[index_file] != 0){

        if(file[index_file] == type[index_type]){
            
            compt += 1;
            index_type += 1;

        }else{
            
            compt = 0;
            index_type = 0;
        }

        index_file += 1;
    }

    if (size == compt){

        return 1;
    }else{
        
        return 0;
    }
}