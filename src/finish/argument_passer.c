#include "my_tar.h"

void argument_passer(char* flague, t_commutator* commutator, char** av, int ac){

    // int index_string = 1;

    // for (int i = 0; i <= ac; i++)
    // {
    //     printf("%d => {%s} %p\n", i, av[i], av[i]);
    // }

    int index = 0;

    t_commutator* tmp_commutator = commutator;

    if(flague[index] == '-'){

        char** archive = malloc(sizeof (char *) * (ac + 1));; // j'alloue des chaine de caractères
        archive = init_file_var(av, ".tar", archive);

        printf("archive = %s\n", archive[0]);

        // for (int i = 0; i < ac; i++)
        // {
        //     printf("=) %d => (%s) %p\n", i, archive[i], archive[i]);
        // }


        char** fils = malloc(sizeof (char *) * (ac + 1)); // j'alloue des chaine de caractères (pas des char) coin coin

        #ifdef __linux__
        printf("fils fait %d octets en mémoire\nqu'un char * fait  %d\n", 
        (int) malloc_usable_size(fils), 
        (int) sizeof(char *)
        );
        #endif

        fils = init_file_var(av, ".c", fils);
        
        index += 1;

        while (flague[index] != 0)
        {

            while (tmp_commutator->commutator != 0){

                if (flague[index] == tmp_commutator->commutator){
                    
                    // printf("jpp\n");

                    // for (int i = 0; archive[i] != NULL; i++)
                    // {
                    //     printf("O_O %d => (%s) %p\n", i, archive[i], archive[i]);
                    // }
                    // printf("melon\n");
                    tmp_commutator->func(archive, fils);
                    tmp_commutator = commutator;

                    // printf("fin jpp\n");
                    break;

                }else{

                    tmp_commutator += 1;
                }
                
            }

            index += 1;
        }


        for (int i = 0; archive[i] != NULL; i++)
        {
            free(archive[i]);
        }
        for (int i = 0; fils[i] != NULL; i++)
        {
            free(fils[i]);
        }
        free(fils);
        free(archive);
    }
    
}