#include "my_tar.h"

void complete_file(char* file, int fd_archive){

    tar_t struct_tar;
    struct stat stat_fils;

    stat(file, &stat_fils);

    my_memset(struct_tar.block, 0, 512);
    my_strcpy(file, struct_tar.name);
    my_strcpy(convertiseur_base(stat_fils.st_mode & 0777, 8, 8), struct_tar.mode);
    my_strcpy(convertiseur_base(stat_fils.st_uid & 0777, 8, 8), struct_tar.unid);
    my_strcpy(convertiseur_base(stat_fils.st_gid & 0777, 8, 8), struct_tar.gid);
    my_strcpy(convertiseur_base(stat_fils.st_size & 0777, 8, 12), struct_tar.size);
    printf("m_time = %ld", stat_fils.st_mtimespec.tv_sec);
    my_strcpy(convertiseur_base(stat_fils.st_mtimespec.tv_sec , 8, 12), struct_tar.mtime);
    my_strcpy(convertiseur_base(stat_fils. & 0777, 8, 12), struct_tar.check);

    printf("name = %s\n", struct_tar.name);
    printf("mode = %s\n", struct_tar.mode);

    write(fd_archive, struct_tar.block, 512);
}