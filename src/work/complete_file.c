#include "my_tar.h"

void write_fd_archive(int fd, char *data, int size){

    printf("data = %s size = %d\n",data, size);
    if (write(fd, data, size) == size){

        // write(fd, data, sizeof(data));
        printf("sortie\n");
        // exit(1);
    }else{

        printf("exit\n");
        exit(-1);
    }

}



static void print_tar_struct(struct tar_s* tar_struct, int fd_archive){

    printf("name\n");
    write_fd_archive(fd_archive, tar_struct->name, sizeof(tar_struct->name));
    printf("mode\n");
    write_fd_archive(fd_archive, tar_struct->mode, sizeof(tar_struct->mode));
    write_fd_archive(fd_archive, tar_struct->unid, sizeof(tar_struct->unid));
    write_fd_archive(fd_archive, tar_struct->gid, sizeof(tar_struct->gid));
    write_fd_archive(fd_archive, tar_struct->size, sizeof(tar_struct->size));
    write_fd_archive(fd_archive, tar_struct->mtime, sizeof(tar_struct->mtime));
    write_fd_archive(fd_archive, tar_struct->check, sizeof(tar_struct->check));
    write_fd_archive(fd_archive, &tar_struct->link, sizeof(tar_struct->link));
    write_fd_archive(fd_archive, tar_struct->link_name, sizeof(tar_struct->link_name));
    write_fd_archive(fd_archive, tar_struct->ustar, sizeof(tar_struct->ustar));
    write_fd_archive(fd_archive, tar_struct->owner, sizeof(tar_struct->owner));
    write_fd_archive(fd_archive, tar_struct->group, sizeof(tar_struct->group));
    write_fd_archive(fd_archive, tar_struct->major, sizeof(tar_struct->major));
    write_fd_archive(fd_archive, tar_struct->minor, sizeof(tar_struct->minor));
    write_fd_archive(fd_archive, tar_struct->prefix, sizeof(tar_struct->prefix));

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
    
    print_tar_struct(struct_tar, fd_archive);

    // write(fd_archive, struct_tar->block, 512);
}
