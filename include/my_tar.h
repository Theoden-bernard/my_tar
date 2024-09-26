#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef __linux__
    #include <sys/sysmacros.h>   // For major() and minor() on Linux
#elif defined(__APPLE__) && defined(__MACH__)
    // macOS should have these in <sys/types.h> or <sys/stat.h>
    #include <sys/types.h>
#endif

#include <fcntl.h>

#include <pwd.h>
#include <grp.h>


#include "define.h"

void argument_passer(char*, t_commutator*, char**, int ac);
int my_strlen(char*);
int creat_fils_tar(char**, char**);
int test_fils_tar(char**, char**);
int append_fils_tar(char**, char**);
int extract_fils_tar(char**, char**);
int update_fils_tar(char**, char**);
int check_type_file(char*, char*);
char* my_strcpy(char* src, char* dest);
char** init_file_var(char**, char*, char**);
char* my_realloc(char* str, int size);
int wordlen(char**);
void write_in_fils_tar(char**, char*);
struct tar_s* complete_file(char*, int, struct tar_s*, struct tar_s*);
void my_memset(void*, int, size_t);
char* int_to_char(int);
int int_len(int);
char* convertiseur_base(int, int, int);
char* my_bzero(char*, int);
int calcul_checksum(char*);
int is_a_tar_file(char* );