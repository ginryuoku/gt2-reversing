// thanks to Nenkai for the solve!
// compiles only with 2.95.2
#include "common.h"

void bcopy(char*, char*, u32);       /* extern */
s32 gt2_main_strlen(signed char*);   /* extern */

char* gt2_main_strcpy(char* dst, char* src, u32 len) {
    u32 str_len = gt2_main_strlen(src) + 1;
    if (len < str_len) 
        str_len = len;
    
    bcopy(src, dst, str_len);
    return dst;
}
