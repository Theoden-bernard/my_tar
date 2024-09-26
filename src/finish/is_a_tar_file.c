#include "my_tar.h"

int is_a_tar_file(char* file){

    struct tar_s tar_struct;

    int fd_file = open(file, O_RDONLY);

    read(fd_file, &tar_struct, sizeof(tar_struct));

    unsigned long index = 0;

    while (index < sizeof(tar_struct.origine_name))
    {
        
        if (tar_struct.origine_name[index] < 32 || tar_struct.origine_name[index] > 126)
        {
            if (tar_struct.origine_name[index] != 0 && tar_struct.origine_name[index] != 10)
            {
                return 0;
            }
            
        }
        
        
        index += 1;
    }

    if (index < 100)
    {
        return 0;
    }
    
    
    return 1;
}