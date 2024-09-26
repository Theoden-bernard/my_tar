#include "my_tar.h"

int test_fils_tar(char** archive, char** fils){

    if (is_a_tar_file(archive[0]) == 1)
    {
        printf("%lu\n", sizeof(tar_t));

        (void)fils;
        // (void)archive;
        printf("is_a_tar_file = %d\n", is_a_tar_file(archive[0]));
        printf("T flag detected\n");
        struct tar_s* tar;
        tar = malloc(sizeof(*tar));
        int fd_archive = open(archive[0], O_RDONLY);
        read(fd_archive, tar, sizeof(tar));

        printf("name: %s\n", tar->origine_name);
        tar = tar->next;
        printf("name: %s\n", tar->origine_name);

        close(fd_archive);
        
    }else{

        write(1, "ceci n'ai pas un fichier tar", 28);
        write(1, "\n", 1);
        return -1;
    }


    return 1;
}