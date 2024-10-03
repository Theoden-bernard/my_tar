#include "my_tar.h"
#include <errno.h>

void write_in_fils_tar(char** fils, char* archive){

    struct stat stat_fils;
    struct tar_s* struct_tar = malloc(sizeof(* struct_tar));

    struct tar_s* first_poiteur = struct_tar;

    int fd_archive = open(archive, O_CREAT | O_WRONLY, S_IRUSR| S_IWUSR);

    int index = 0;
 
    int fd_fils = 0;

    // printf("fd_fils = %d\n", fd_fils);

    char buff[500];

    my_memset(buff, 0, 500);

    if (fd_fils != -1 && fd_archive != -1) //attention petit bug a penser a resoutre ma fonction ecrit meme les fichier inexistant ce qu'il ne faut pas 
    {   

        
        while (fils[index] != 0){

            struct tar_s* next_struct_tar = malloc(sizeof(* next_struct_tar));
            stat(fils[index], &stat_fils);
            char* text = malloc(sizeof(char) * stat_fils.st_size);

            complete_file(fils[index], fd_archive, struct_tar);
            
            struct_tar->next = next_struct_tar;
            struct_tar = struct_tar->next;

            fd_fils = open(fils[index], O_APPEND);
            read(fd_fils, text, stat_fils.st_size);

            write(fd_archive, text, stat_fils.st_size);
            write(fd_archive, buff, 500);
            close(fd_fils);
            // printf("text = %s\n", text);
            index += 1;
            // printf("write in file\n");
            free(text);
            // free(next_struct_tar);
        }

        
    }
    close(fd_archive);
    printf("toto\n");

    struct_tar = first_poiteur;

    free(struct_tar);

    struct tar_s* struct_tar_2 = malloc(sizeof(*struct_tar_2));
    
    int fd_archive_2 = open(archive, O_CREAT | O_WRONLY, S_IRUSR| S_IWUSR);
    printf("fd_archive_2 = %d\n", fd_archive_2);

    printf("read = %zd \n",read(fd_archive_2, struct_tar_2, sizeof(struct tar_s))); // read return -1 donc il y a une erreuré
    
    perror("");

    printf("struct_name = %s\n" , struct_tar_2->name);
    write(1,"struct_tar_2 = ", my_strlen("struct_tar_2 = "));
    write(1, struct_tar_2->name, sizeof(struct_tar_2->name));
    write(1,"\n", 1);
    struct_tar_2 = struct_tar_2->next;
    write(1,"struct_tar_2 = ", my_strlen("struct_tar_2 = "));
    write(1, struct_tar_2->name, sizeof(struct_tar_2->name));
    write(1,"\n", 1);
}