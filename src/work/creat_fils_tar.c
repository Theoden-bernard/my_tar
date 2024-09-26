#include "my_tar.h"

// cette fonction doit prendre en paramettre un fichier parent(.tar) et des fichier enfant(.c) 

/*pour l'instant la fonction est juste capable de crée un fichier .tar en fonction de ce que je lui envoie*/

int creat_fils_tar(char** archive, char** fils){

    FILE *fp = NULL;

    printf("C flag detected\n");

    if(check_type_file(archive[0], ".tar") == 1){

        printf("bug\n");

        fp = fopen (archive[0], "rw");
        
        printf("debug\n");

        write_in_fils_tar(fils, archive[0]);
        
    }
    
    fclose(fp);

    return 1;
}