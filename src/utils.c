/*
**
*/
// #include "utils.h"
#include <stdio.h>
#include "my_tar.h"

/*
**
*/
void my_memset(char *buff, char c, int size) {
  int index = 0;

  while (index < size) {
    buff[index] = c;
    index += 1;
  }
}

void my_bzero(char *buff, int size){
  my_memset(buff, 0, size);
}

char *my_malloc(int size) {
  char *buff = malloc(size);

  if (buff == NULL) {
    exit(1);
  }

  my_bzero(buff, size);
  
  return buff;
}

struct stat* my_stat(char* path, struct stat* stat_fil){
  
  if (stat(path, stat_fil) == -1){
    
    printf("can't stat [%s]\n", path);
    perror("error");
    exit(1);
  }

  return stat_fil;
}

int my_read(int fd, char* buff, int size){

  if(read(fd, buff, size) < 0){
    
    printf("con't read [%s]\n", buff);
    perror("error");
    exit(1);
  }else{
    
    return 1;
  }
}

t_list *init_list(void){
  return (t_list *)my_malloc(sizeof(t_list));
}

t_list *add_elem(t_list *list, void *elem) {
  t_list *new_elem = (t_list *)my_malloc(sizeof(t_list));
    
  new_elem->elem = elem;
  new_elem->next = list;

  return new_elem;
}

void apply_to_list(t_list *list, void (*func)(void *elem, void *param), void *other){
  
  if (list == 0)
  { 
    func(list, other);
  }
  
  while (list != 0){ //list est egale a null donc je doit ecrire tout les fichier de ma tarball.
    // printf("toto\n");
    //   my_print_list(list->elem);
    func(list->elem, other);
    list = list->next;
  }
}

int string_compare(char* str_archive, char* str_extract){
  
  int index = 0;

//   printf("str_archive = %s\n", str_archive);
//   printf("str_extract = %s\n", str_extract);

  while(str_archive[index] == str_extract[index] && str_archive[index] != 0){
    // printf("str_archive = %c\n", str_archive[index]);
    // printf("str_extract = %c\n", str_extract[index]);
    index += 1;
  }

  if (str_archive[index] == 0){
    return 1;
  }else{
    return 0;
  }
}

t_list* revers_my_list(t_list* my_old_list){

  t_list* my_list = NULL;
  t_list* temp = my_old_list;

  while(temp->next != NULL){
    
    my_list = add_elem(my_list, temp->elem);
    temp = temp->next;
  }

  return my_list;
}

char* reverse_string(char* string){

    int index = strlen(string) - 1;
    int index_new = 0;

    char* new_string = my_malloc(strlen(string));

    while (string[index_new] != 0) {
        
        new_string[index_new] = string[index];
        index_new += 1;
        index -= 1;
    }

    strcpy(string, new_string);

    free(new_string);
    
    return string;
}

int pwr(int base, int power){

    int result = 1;

    while (power > 0) {
        
        result *= base;
        power -= 1;
    }
    return result;
}

int convertiseur_base_10(char* base, int base_init){

    int power = 0;

    int num_base = char_to_int(base);

    int result = 0;
    int stock = 0;

    while (num_base != 0) {
        
        stock = num_base % 10; // ex 651 on prend le 1;

        stock = stock * pwr(base_init , power); // 1 fois base puissance power (ex 1*8^0);

        result = result + stock;

        num_base = num_base / 10; // ex 651 on prend 65 car 651/10;
        power += 1;
    }

    return result;
}

char* convertiseur_base(int base_10, int base, int size){

    int index = 0;
    char* storage = my_malloc(sizeof(char) * size);
    int result = 0;
    int last_number = 0;

    my_memset(storage, '0', size);

    while (base_10 != 0)
    {

        last_number = (base_10 % base);

        result = (base_10 - (base_10 % base)) / base/* % base*/; 

        if (last_number > 9){

            storage[index] = last_number + 'A' - 9;
        }else{

            storage[index] = last_number + '0';
     
        }

        base_10 = result;
        index += 1;
    }

    // printf("storage_befor = %d\n", storage[0]);

    strcpy(storage ,reverse_string(storage));

    // printf("storage_after = %d\n", storage[0]);
    
    return storage;
}