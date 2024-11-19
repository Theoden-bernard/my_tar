/*
**
*/
#include "my_tar.h"

/*
**
*/
int get_opt(char *str) {
  int options = 0;
  t_opt_list opt_list[] ={
    {OPT_FILE, 'f'},
    {OPT_CREATE, 'c'},
    {OPT_LIST, 't'},
    {OPT_EXTRACT, 'x'},
    {OPT_APPEND, 'r'},
    {OPT_UPDATE, 'u'},
    {0, 0}
  };

  while (*str) {
    for (t_opt_list *tmp_opt_list = opt_list ; tmp_opt_list->c != 0 ; tmp_opt_list += 1) {
      if (*str == tmp_opt_list->c) {
	      options += tmp_opt_list->num;
      }
    }
    str += 1;
  }

  return options;
}

t_option *init_struct_opt() {
  t_option *options = (t_option *)my_malloc(sizeof(t_option));
  options->file_list = init_list();

  return(options);
}

void usage(){
  printf("tar kqjsjdfokqsjdkfklkqsdj\n");
  exit(1);
}

t_option *init_options(int ac, char **av) {
  t_option *options = init_struct_opt();

  for (int index = 1 ; index < ac ; index += 1) {
    if (av[index][0] == '-') {
      options->opt += get_opt(&(av[index][1]));
      if (options->opt & OPT_FILE) {
        if(options->opt & OPT_CREATE){
          remove(av[index + 1]);
        }
        if (index + 1 < ac) {
          options->tar_filename = av[index + 1];
          index += 1;
        } else {
          usage();
        }
      }
    } else {

        // printf("av[index] = %s\n", av[index]);
        if (open(av[index],  O_RDONLY) != -1) {

            t_tar *elem = tar_t_from_filename(av[index], options->opt);
            options->file_list = add_elem(options->file_list, (void *)elem); // <-- je bosse sur cette ligne (pouquoi elem est un void *)
        }else {

            char* buff = malloc(sizeof(char) * strlen("my_tar:  "));
            strcpy(buff, "my_tar: ");
            write(2, buff, strlen(buff));
            write(2, av[index], strlen(av[index]));
            buff = realloc(buff,strlen(" : Cannot stat: No such file or directory "));
            strcpy(buff, ": Cannot stat: No such file or directory");
            write(2, buff, strlen(buff));
            write(1, "\n", 1);
            free(buff);
        }
    }
    
  }
  options->file_list = revers_my_list(options->file_list);
  
  return options;
}
