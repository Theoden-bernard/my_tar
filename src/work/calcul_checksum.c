#include "my_tar.h"

int calcul_checksum(char* file){

    int index = 0;
    int checksum = 0;

    while (index != 512)
    {
        if (index >= 148 && index < 156) {
            
            checksum += ' ';
        } else {
            checksum += (unsigned char)file[index];
        }

        index += 1;
    }
    
    return checksum;
}