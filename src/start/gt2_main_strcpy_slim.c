// thanks to Nenkai for the solve!
// compiles only with 2.8.1
#include "common.h"

u8* gt2_main_strcpy_slim(u8* dest, u8* src) { // this is a strcpy

    u8 value;
    u8* cur = dest;
    do
    {
        value = *src++;
        *cur++ = value;
    } while (value << 24); // Essentially clears the upper 24 bits, ensuring that the current value is only 0-255 (ascii)
    
    return dest;
}
