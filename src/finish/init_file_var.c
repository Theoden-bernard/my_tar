/*fonction qui me permettera de transphere le nom de l'archibe de av vers un char * archive */

#include "my_tar.h"

char** init_file_var(char** av, char* type, char** fils){

    int index = 0;
    int size = 0;
    int index_fils = 0;

    if (type[1] == 't' && type[2] == 'a' && type[3] == 'r' && type[4] == '\0')
    {
        // printf("lunette\n");
        while (av[index] != 0 && check_type_file(av[index], type) == 0)
        {
            index += 1;
            // printf("phone => %s\n", av[index]);
            if (check_type_file(av[index], type) == 1)
            {
                size = my_strlen(av[index]);
                // printf("size => %d\n", size);
                fils[index_fils] = malloc(sizeof(char) * size);
                // printf("tata => %s\n", av[index]);
                my_strcpy(av[index], fils[index_fils]);
                index_fils += 1;
            }
            
        }
        
    }else{
        // printf("AV[%d] = = > %s\n", index, av[index]);
        while (av[index] != 0)
        {   
            if (check_type_file(av[index], type) == 1)
            {   
                size = my_strlen(av[index]);
                fils[index_fils] = malloc(sizeof(char) * size + 1);
                // printf("tatu\n");
                my_strcpy(av[index], fils[index_fils]);
                index_fils += 1;
            }
            index += 1;
        }
    }

    fils[index_fils] = NULL;
    return fils;
}