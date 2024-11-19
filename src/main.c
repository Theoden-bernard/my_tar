/*
**
*/
#include "my_tar.h"

/*
**
*/
int main(int ac, char **av){

  t_option *options = init_options(ac, av);

  if (options) {

    if (options->opt & OPT_CREATE) {
      int fd = open_tar_file(options, O_APPEND | O_WRONLY | O_CREAT);

      apply_to_list(options->file_list, add_file_to_archive, (void *)(&fd));
      
      close(fd);
    }
    
    if((options->opt & OPT_LIST) && (options->opt & OPT_FILE) && options->tar_filename){

      list_file_from_tar(options);
    }

    if((options->opt & OPT_EXTRACT) && (options->opt & OPT_FILE) && options->tar_filename){

      apply_to_list(options->file_list, extract_file, (void *)(options));

    }

    if((options->opt & OPT_APPEND) && (options->opt & OPT_FILE) && options->tar_filename){

      int fd = open_tar_file(options, O_APPEND | O_WRONLY | O_CREAT);

      apply_to_list(options->file_list, add_file_to_archive, (void *)(&fd));
      
      close(fd);
    }

    if((options->opt & OPT_UPDATE) && (options->opt & OPT_FILE) && options->tar_filename){
      
      apply_to_list(options->file_list, update_archive, (void *)(options));
    }
  }

  return 0;
}