#include "my_tar.h"

int calcul_checksum(struct tar_s* struct_tar){

    int index = 0;
    int checksum = 0;

    // (void)file;

    while (index != 512)
    {
        if (index >= 148 && index < 156) {
            
            checksum += ' ';
        } else {
            checksum += (unsigned char)struct_tar->block[index];
        }

        index += 1;
    }
    
    return checksum;
}