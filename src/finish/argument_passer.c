#include "my_tar.h"

void argument_passer(char* flague, t_commutator* commutator, char** av, int ac){

    // int index_string = 1;

    int index = 0;

    t_commutator* tmp_commutator = commutator;

    if(flague[index] == '-'){

        char** archive = malloc(sizeof (char *) * (ac));; // j'alloue des chaine de caractères
        archive = init_file_var(av, ".tar", archive);
        
        char** fils = malloc(sizeof (char *) * (ac)); // j'alloue des chaine de caractères (pas des char) coin coin
        fils = init_file_var(av, ".c", fils);
        
        index += 1;

        while (flague[index] != 0)
        {

            while (tmp_commutator->commutator != 0){

                if (flague[index] == tmp_commutator->commutator){
                    
                    printf("jpp\n");

                    tmp_commutator->func(archive, fils);
                    tmp_commutator = commutator;

                    printf("fin jpp\n");
                    break;

                }else{

                    tmp_commutator += 1;
                }
                
            }

            index += 1;
        }
        free(fils);
        free(archive);
    }
    
}