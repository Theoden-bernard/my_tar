#include "my_tar.h"

void write_in_fils_tar(char** fils, char* archive){

    struct stat stat_fils;
    struct tar_s* struct_tar = malloc(sizeof(* struct_tar));

    struct tar_s* first_poiteur = struct_tar;

    int fd_archive = open(archive, O_CREAT | O_WRONLY, S_IRUSR);

    int index = 0;

    int fd_fils = 0;

    // while (fils[index])
    // {
    //     printf("fild[%d] (%s) => %s\n", index, fils[index], fils[index]);
    //     index++;
    // }
    


    printf("fd_fils = %d\n", fd_fils);
    printf("fd_archive = %d\n", fd_archive);

    char buff[500];

    my_memset(buff, 0, 500);

    if (fd_fils != -1 && fd_archive != -1) //attention petit bug a penser a resoutre ma fonction ecrit meme les fichier inexistant ce qu'il ne faut pas 
    {   

        
        while (fils[index] != 0){

            struct tar_s* next_struct_tar = malloc(sizeof(* next_struct_tar));
            stat(fils[index], &stat_fils);
            char* text = malloc(sizeof(char) * stat_fils.st_size);

            // printf("index = %d\n", index);
            // printf("fils[index] = %s\n", fils[index]);
            /*struct_tar = */complete_file(fils[index], fd_archive, struct_tar);
            
            // printf("struct_tar = %s\n", struct_tar->name);


            struct_tar->next = next_struct_tar;
            struct_tar = struct_tar->next;

            fd_fils = open(fils[index], O_APPEND);
            read(fd_fils, text, stat_fils.st_size);
            // write(fd_archive, NULL, 500);
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

    struct_tar = first_poiteur;
    free(struct_tar);
    
}