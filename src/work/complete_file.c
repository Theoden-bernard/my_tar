#include "my_tar.h"

struct tar_s* complete_file(char* file, int fd_archive, struct tar_s* struct_tar, struct tar_s* new_struct){

    // tar_t struct_tar;


    struct stat stat_fils;

    struct passwd stat_id; //structure qui sontien tout sur l'utilisateur
    struct group stat_group; // structure qui contien tout sur le groupe

    stat(file, &stat_fils);

    my_memset(struct_tar->block, 0, sizeof(struct_tar));
    

    my_strcpy(file, struct_tar->name);
    
    
    my_strcpy(convertiseur_base(stat_fils.st_mode & 0777, 8, 8), struct_tar->mode);
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

    my_strcpy(convertiseur_base(calcul_checksum(file), 8, 8), struct_tar->check);
    
    my_strcpy("0", &struct_tar->link);
    
    my_strcpy("ustar", struct_tar->ustar);
    
    stat_id = *getpwuid(stat_fils.st_uid);
    printf("bug\n");
    my_strcpy(stat_id.pw_name, struct_tar->owner);
    
    stat_group = *getgrgid(stat_fils.st_gid);
    my_strcpy(stat_group.gr_name, struct_tar->group);
    
    my_strcpy(convertiseur_base(major(stat_fils.st_rdev), 10, 8), struct_tar->major);
    
    my_strcpy(convertiseur_base(minor(stat_fils.st_rdev), 10, 8), struct_tar->minor);
    
    write(fd_archive, struct_tar->block, sizeof(struct_tar));
    
    struct_tar->next = new_struct;

    return new_struct;
}