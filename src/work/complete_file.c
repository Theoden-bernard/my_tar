#include "my_tar.h"

static void print_tar_struct(struct tar_s* tar_struct){

    printf("%s\n", tar_struct->name);
    printf("%s\n", tar_struct->mode);
    printf("%s\n", tar_struct->unid);
    printf("%s\n", tar_struct->gid);
    printf("%s\n", tar_struct->size);
    printf("%s\n", tar_struct->mtime);
    printf("%s\n", tar_struct->check);
    printf("%d\n", tar_struct->link);
    printf("%s\n", tar_struct->link_name);
    printf("%s\n", tar_struct->ustar);
    printf("%s\n", tar_struct->owner);
    printf("%s\n", tar_struct->group);
    printf("%s\n", tar_struct->major);
    printf("%s\n", tar_struct->minor);
    printf("%s\n", tar_struct->prefix);

}

void complete_file(char* file, int fd_archive, struct tar_s* struct_tar){

    // tar_t struct_tar;


    struct stat stat_fils;

    struct passwd stat_id; //structure qui sontien tout sur l'utilisateur
    struct group stat_group; // structure qui contien tout sur le groupe


    stat(file, &stat_fils);

    my_memset(struct_tar->block, 0, sizeof(struct_tar->block));
    printf("jpp %d\n", (int) sizeof(struct_tar->block));

    printf("file = %s\n", file); //le probleme viens de file
    printf("struct->name = %s\n", struct_tar->name);

    my_strcpy(file, struct_tar->name);

    
    char* value = malloc(sizeof(char)* 9);
    my_strcpy(convertiseur_base(stat_fils.st_mode & 0777, 8, 8), value);

    printf("test = %s\n", value);

    printf("buggg_2\n");
    printf("my_strcpy = %s\n" ,my_strcpy(value, struct_tar->mode));
    printf("buggg\n");
    my_strcpy(convertiseur_base(stat_fils.st_uid & 0777, 8, 8), struct_tar->unid);
    my_strcpy(convertiseur_base(stat_fils.st_gid & 0777, 8, 8), struct_tar->gid);
    my_strcpy(convertiseur_base(stat_fils.st_size & 0777, 8, 12), struct_tar->size);
    

    #ifdef __linux__
            
            my_strcpy(convertiseur_base(stat_fils.st_mtim.tv_sec , 8, 12), struct_tar->mtime); 
        #elif defined(__APPLE__) && defined(__MACH__)  // For macOS (BSD)
            
            my_strcpy(convertiseur_base(stat_fils.st_mtimespec.tv_sec , 8, 12), struct_tar->mtime);
        #else
            printf("Unknown platform\n");
        #endif

    my_strcpy(convertiseur_base(calcul_checksum(struct_tar), 8, 8), struct_tar->check);
    
    my_strcpy("0", &struct_tar->link);
    
    my_strcpy("ustar", struct_tar->ustar);
    
    stat_id = *getpwuid(stat_fils.st_uid);
    // printf("bug\n");
    my_strcpy(stat_id.pw_name, struct_tar->owner);
    
    stat_group = *getgrgid(stat_fils.st_gid);
    my_strcpy(stat_group.gr_name, struct_tar->group);

    
    my_strcpy(convertiseur_base(major(stat_fils.st_rdev), 10, 8), struct_tar->major);
    
    my_strcpy(convertiseur_base(minor(stat_fils.st_rdev), 10, 8), struct_tar->minor);
    
    print_tar_struct(struct_tar);

    write(fd_archive, struct_tar->block, 512);
}
