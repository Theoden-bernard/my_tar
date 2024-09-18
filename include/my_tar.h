#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <fcntl.h>


#include "define.h"

void argument_passer(char*, t_commutator*, char**, int ac);
int my_strlen(char*);
void creat_fils_tar(char**, char**);
void test_fils_tar(char**, char**);
void append_fils_tar(char**, char**);
void extract_fils_tar(char**, char**);
void update_fils_tar(char**, char**);
int check_type_file(char*, char*);
char* my_strcpy(char* src, char* dest);
char** init_file_var(char**, char*, char**);
char* my_realloc(char* str, int size);
int wordlen(char**);
void write_in_fils_tar(char**, char*);
void complete_file(char*, int);
void my_memset(void*, int, size_t);
char* int_to_char(int);
int int_len(int);
char* convertiseur_base(int, int, int);
char* my_bzero(char*, int);