#include "my_tar.h"

void write_in_fils_tar(char** fils, char* archive){

    struct stat stat_fils;

    int fd_fils = 0;
    int fd_archive = 0;

    int index = 0;

    
    fd_archive = open(archive, O_CREAT | O_WRONLY, S_IRUSR);


    printf("fd_fils = %d\n", fd_fils);
    printf("fd_archive = %d\n", fd_archive);

    if (fd_fils != -1 && fd_archive != -1) //attention petit bug a pencer a resoutre ma fonction ecrit meme les fichier inexistant ce qu'il ne faut pas 
    {   
        
        char* text = malloc(sizeof(char) * stat_fils.st_size);
        while (fils[index] != 0){

            stat(fils[index], &stat_fils);
            complete_file(fils[index], fd_archive);
            fd_fils = open(fils[index], O_APPEND);
            // write(fd_archive, fils[index], my_strlen(fils[index]));
            // printf("stat %s = %lld\n",fils[index], stat_fils.st_size);
            read(fd_fils, text, stat_fils.st_size);
            write(fd_archive, text, stat_fils.st_size);
            close(fd_fils);
            // printf("text = %s\n", text);
            index += 1;
        }
        free(text);
    }
    
}