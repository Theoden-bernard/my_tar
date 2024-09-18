/*fonction qui me permettera de transphere le nom de l'archibe de av vaire un char * archive */

#include "my_tar.h"

char** init_file_var(char** av, char* type, char** fils){

    int index = 0;
    int size = 0;
    int index_fils = 0;

    if (type[1] == 't' && type[2] == 'a' && type[3] == 'r' && type[4] == '\0')
    {
        while (av[index] != 0 && check_type_file(av[index], type) == 0)
        {
            index += 1;
            
            if (check_type_file(av[index], type) == 1)
            {   
                size = my_strlen(av[index]);
                fils[index_fils] = malloc(sizeof(char) * size);
                my_strcpy(av[index], fils[index_fils]);
                index_fils += 1;
            }
        }
        
    }else{
        
        while (av[index] != 0)
        {   
            if (check_type_file(av[index], type) == 1)
            {   
                size = my_strlen(av[index]);
                fils[index_fils] = malloc(sizeof(char) * size + 1);
                my_strcpy(av[index], fils[index_fils]);
                index_fils += 1;
            }
            index += 1;
        }
    }
    
    index_fils = 0;

    return fils;
}