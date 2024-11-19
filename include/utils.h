/*
**
*/
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
/*
**
*/
typedef struct s_list{
  void *elem;
  struct s_list* next;
} t_list;

/*
**
*/
char *my_malloc(int);
void my_memset(char *, char, int);
void my_bzero(char *, int);
struct stat* my_stat(char*, struct stat*);
int my_read(int, char*, int);
t_list *init_list(void);
t_list *add_elem(t_list *, void *);
void apply_to_list(t_list *, void (*func)(void *, void *), void *);
t_list* revers_my_list(t_list*);
int convertiseur_base_10(char*, int);
char* convertiseur_base(int, int, int);