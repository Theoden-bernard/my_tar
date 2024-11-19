/*
**
*/
#include <stdio.h>
#include "my_tar.h"

/*
**
*/

int int_len(int integer){

    int index = 0;

    while (integer != 0)
    {   
        integer = integer / 10;
        index += 1;
    }
    
    return index;
}

char* int_to_char(int integer){
    int zero_in_char = 48;
    int index = 0;
    int size = int_len(integer) - 1; 
    
    char* str = malloc(sizeof(char) * size);

    while (integer != 0)
    {
        
        index = 0;
        zero_in_char = 48;

        while(integer % 10 != index){

            zero_in_char += 1;
            index += 1;
        }

        str[size] = zero_in_char;
        
        size -= 1;

        integer = integer / 10;
    }

    return str;
}

int char_to_int(char* str){

  int index = 0;
  int num = 48;
  int result = 0;
  // printf("str = %s\n", str);

  while (str[index] != 0)
  {
    
    while (num < str[index])
    {
      result += 1;
      num += 1;
    }
    
    index += 1;
    
    if (str[index] != 0)
    {
      result = result * 10;
    }
    
    num = 48;
  }

  return result;
}

t_tar *tar_t_from_filename(char *filename, int opt) {
  t_tar *elem = init_tar_t();

    // struct passwd stat_id;
    // struct group stat_group;
  
  strcpy(elem->filename, filename);
  
  if (opt & OPT_CREATE || opt & OPT_APPEND || opt & OPT_UPDATE)
  {
    struct stat* stat_fil = (struct stat*)my_malloc(sizeof(struct stat));
    stat_fil = my_stat(filename, stat_fil);
    my_memset(elem->mode, '0', 7);
    // strcpy(elem->mode, convertiseur_base(stat_fil->st_mode & 0777, 8, 8));
    my_memset(elem->uid, '0', 7);
    // strcpy(elem->uid, convertiseur_base(stat_fil->st_uid & 0777, 8, 8));
    my_memset(elem->gid, '0', 7);
    // strcpy(elem->gid, convertiseur_base(stat_fil->st_gid & 0777, 8, 8));

    my_memset(elem->chksum, '0', 6);

    strcpy(&elem->typeflag, "0");

    strcpy(elem->magic , "ustar");
    // strcpy(elem->ustar, "ustar");

    // stat_id = geteuid(stat_fil->st_uid);
    my_memset(elem->uname, '0', 31);

    // stat_group = *getegid(stat_fil->st_gid);
    // strcpy(elem->gname, stat_group->gr_name);

    my_memset(elem->gname, '0', 31);

    // my_memset(elem->devmajor, '0', 7);
    // my_memset(elem->devminor, '0', 7);
    // my_memset(elem->prefix, '0', 155);

    // strcpy(elem->devmajor, convertiseur_base(major(stat_fil->st_rdev), 10, 8));
    
    // strcpy(elem->devminor, convertiseur_base(minor(stat_fil->st_rdev), 10, 8));

    int size = stat_fil->st_size;
    // my_memset(elem->size, '0', 11);
    strcpy(elem->size, convertiseur_base(size, 8, 11));
    strcpy(elem->mtime, convertiseur_base(stat_fil->st_mtim.tv_sec , 8, 11));

  }
  
  return elem;
}

void my_print_list(void *elem){
  printf("--->%p\n", elem);
  printf("-- filename: [%s]\n", ((t_tar *)elem)->filename);
}

int open_tar_file(t_option *options, int flag) {

  int fd = open(options->tar_filename, flag, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

  if (fd < 0) {
    printf("Can't open archive file [%s]\n", options->tar_filename);
    perror("error");
    exit(1);
  }

  return fd;
}

void write_tar_file(int fd, void* data, int size) {

  if (write(fd, data, size) != size) {
    printf("Can't write in tar file\n");
    perror("");
    exit(1);
  }
}

void print_elem(void* elem, void* not_use){

  (void)not_use;
  printf("--- %s\n", ((t_tar *)elem)->filename);
}

void add_file_to_archive(void *elem, void *fd) {

  write_tar_file(*(int *)fd, ((t_tar *)elem), sizeof(t_tar));
  int fd_file = open(((t_tar *)elem)->filename, O_RDONLY);

  char* buff = malloc(sizeof(char) * 512);

    int my_read = 0;

    int size = convertiseur_base_10(((t_tar *)elem)->size, 8);

  for (int i = 0; i < size ;i += my_read) {

    my_bzero(buff, sizeof(t_tar));
    my_read = read(fd_file, buff, sizeof(t_tar));
    write_tar_file(*(int *)fd, buff, sizeof(t_tar));
  }
    close(fd_file);
}

int nbr_struct_in_tar(int size){

    int index = 0;
    int mult = 0;
    
    mult += 1;
    index = size / mult;

    while (index > 512) {
    
        mult += 1;
        index = size / mult;
    
    }

    return mult;
}

void print_char(char *buff){
    for (int index = 0 ; index < 512 ; index += 1) {
        if ((buff[index] > 'A' && buff[index] < 'z') || (buff[index] >= '0' && buff[index] <= '9')) {
            write(1, &buff[index], 1);
        } else {
            write(1, "_", 1);
        }
    }


}

void list_file_from_tar(t_option* options){

    //t_list* elem = options->file_list;

    int fd = open_tar_file(options, O_RDWR | O_CREAT);

    struct stat* stat_file = (struct stat*)my_malloc(sizeof(struct stat));
    stat_file = my_stat(options->tar_filename, stat_file);

    char* buff = my_malloc(sizeof(t_tar));
    int size = 0;

    t_tar tmp;

  while (read(fd, &tmp, sizeof(t_tar)) > 0) {

        int where = lseek(fd, 0, SEEK_CUR);
        printf("%5d - ", where); 
        print_char((char *)&tmp);
        printf("\n");
  }

    while (read(fd, &tmp, sizeof(t_tar)) > 0) {
        
        size = convertiseur_base_10(tmp.size, 8);
        // printf("size = %d\n",size);
        // printf("(%12s) %d %ld %ld %d\n", tmp.filename, tmp.filename[0] ,sizeof(t_tar), lseek(fd, 0, SEEK_CUR), size);

        if (tmp.filename[0] != 0){

            printf("%s\n", tmp.filename);
        }

        lseek(fd, sizeof(t_tar)* nbr_struct_in_tar(size), SEEK_CUR);
    }

  close(fd);
  free(stat_file);
  free(buff);
}

int verifi_Tar_file(char* flag){
  
  if (flag != NULL)
  {
    if (flag[0] == '-'){
      return 1;
    }else{
      return 0;
    }
  }
  return 0;
}

t_tar* init_tar_t() {
  t_tar* tar = (t_tar *)my_malloc(sizeof(t_tar));
  strcpy(tar->magic, int_to_char(TAR_MAGIC_NUMBER));
  return(tar);
}

void extract_file(void* elem, void* options){

  int fd = open_tar_file((t_option*)options, O_RDWR | O_CREAT);

  struct stat* stat_archive = malloc(sizeof(struct stat));
  stat_archive = my_stat(((t_option*)options)->tar_filename, stat_archive);

  char* buff = my_malloc(sizeof(t_tar));

  int size = 0;

  
    t_tar tmp;

    while (read(fd, &tmp, sizeof(t_tar)) > 0){
    
    size = convertiseur_base_10(tmp.size, 8);

    int bouton  = 0;

    if (elem == 0){
      
      bouton = 2;
    }else{

      bouton = string_compare(tmp.filename, ((t_tar*)elem)->filename);
    }

    if(bouton == 1 || bouton == 2){

        int index = 0;

        if (tmp.filename[strlen(tmp.filename) - 1] == '/') {
            
            mkdir(tmp.filename, 0755);

        }else{
            
            while (index < nbr_struct_in_tar(size)) {
                
                my_read(fd, buff, sizeof(t_tar));

                int fp = open(tmp.filename , O_APPEND | O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                write(fp, buff, size);
                index += 1;
                close(fp);
            }
        }

    }else {

        lseek(fd, sizeof(t_tar)* nbr_struct_in_tar(size),SEEK_CUR);
    }

  }
  
  close(fd);
  free(stat_archive);
  free(buff);

//   return true;
}

void update_archive(void* elem, void* options){
  
  int fd = open_tar_file((t_option*)options,  O_APPEND | O_RDWR | O_CREAT);

  struct stat* stat_archive = malloc(sizeof(struct stat));
  stat_archive = my_stat(((t_option*)options)->tar_filename, stat_archive);

  char* buff = my_malloc(sizeof(t_tar));

  int size = 0;

  for (int index = 0; index < stat_archive->st_size; index += sizeof(t_tar) + size){
    
    lseek(fd, sizeof(((t_tar*)elem)->magic), SEEK_CUR);
    my_read(fd, buff, sizeof(((t_tar*)elem)->filename));

    int bouton = string_compare(buff, ((t_tar*)elem)->filename);
    char* temp = malloc(sizeof(char) * strlen(buff));
    
    if (bouton == 1)
    {
      strcpy(temp, buff);
    }
    
    lseek(fd,sizeof(((t_tar*)elem)->mode) + sizeof(((t_tar*)elem)->uid) + sizeof(((t_tar*)elem)->gid) + sizeof(((t_tar*)elem)->chksum) + sizeof(((t_tar*)elem)->typeflag) + sizeof(((t_tar*)elem)->linkname) + sizeof(((t_tar*)elem)->magic) + sizeof(((t_tar*)elem)->version) + sizeof(((t_tar*)elem)->uname) + sizeof(((t_tar*)elem)->gname) + sizeof(((t_tar*)elem)->devmajor) + sizeof(((t_tar*)elem)->devminor) + sizeof(((t_tar*)elem)->prefix), SEEK_CUR);
    my_read(fd, buff, sizeof(((t_tar*)elem)->size));
    size = char_to_int(buff);
    my_read(fd, buff, sizeof((t_tar*)elem)->mtime);
    // lseek(fd, sizeof((t_tar*)elem)->mtime, SEEK_CUR);
    // write(1, "buff = ", 7);
    // write(1, buff, 13);
    // write(1, "\n", 1);

    if(bouton == 1 && string_compare(buff, ((t_tar*)elem)->mtime) != 1){
    
    //   write(1, buff, 13);
    //   write(1, "\n", 1);
      lseek(fd, 0, SEEK_END);
      apply_to_list(((t_option*)options)->file_list, add_file_to_archive, (void *)(&fd));
    }

    // lseek(fd, size, SEEK_CUR);
  }

  close(fd);
}