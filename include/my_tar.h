/*
**
*/
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
**
*/
// #include <pwd.h>
// #include <grp.h>
/*
**
*/
#include "utils.h"
/*
** 
*/          
#include <assert.h>
#include <errno.h>
/*
**
*/
typedef struct s_tar
{              
  #define TAR_MAGIC_NUMBER 0x12345  // byte offset
  char filename[100];               //   0
  char mode[8];                 // 100
  char uid[8];                  // 108
  char gid[8];                  // 116
  char size[12];                // 124
  char mtime[12];               // 136
  char chksum[8];               // 148
  char typeflag;                // 156
  char linkname[100];           // 157
  char magic[6];                // 257
  char version[2];              // 263
  char uname[32];               // 265
  char gname[32];               // 297
  char devmajor[8];             // 329
  char devminor[8];             // 337
  char prefix[155];             // 345
  char padding[12];             // 500
                                // 512
} t_tar;

typedef struct s_opt_list{
#define OPT_FILE (1<<0)
#define OPT_CREATE (1<<1)
#define OPT_LIST (1<<2)
#define OPT_EXTRACT (1<<3)
#define OPT_APPEND (1<<4)
#define OPT_UPDATE (1<<5)
  int num;
  char c;
} t_opt_list;

typedef struct s_option{
  int opt;
  char *tar_filename;
  t_list *file_list;
} t_option;

typedef struct s_tar_size{
    char padding[8];
    int size;
} t_tar_size;

/*
**
*/
int main(int, char **);
t_option *init_options(int, char **);
t_tar *tar_t_from_filename(char *, int);
int char_to_int(char*);
void my_print_list(void *);
int open_tar_file(t_option *, int);
void write_tar_file(int, void*, int);
void add_file_to_archive(void *, void *);
void print_elem(void*, void*);
void list_file_from_tar(t_option *);
int verifi_Tar_file(char* flag);
t_tar* init_tar_t();
void extract_file(void*, void*);
int string_compare(char*, char*);
void update_archive(void* elem, void* options);