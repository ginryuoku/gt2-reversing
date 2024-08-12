// thanks to Nenkai for the solve!
#include "common.h"

int gt2_main_strlen(signed char* path) {
    int ch;
    int length = -1;
    do 
    {
        ch = *path++;
        length++;
    } while (ch != '\0');
    
    return length;
}
