#include "my_tar.h"

int main(int ac, char** av){
    
    t_commutator commutator[] = {

        {COMMUTATOR_CREAT, creat_fils_tar},
        {COMMUTATOR_TEST, test_fils_tar},
        {COMMUTATOR_APPEND, append_fils_tar},
        {COMMUTATOR_EXTRAXT, extract_fils_tar},
        {COMMUTATOR_UPDATE, update_fils_tar},
        {0,0}
    };

    int compteur = 0;
    while (compteur < ac)
    {
        printf("debug %d -> %s\n", compteur, av[compteur]);
        argument_passer(av[compteur], commutator, av, ac);
        compteur++;
    }
}