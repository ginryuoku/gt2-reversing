// thanks to Nenkai for the solve!

#include "common.h"

// NOTE: >=2.91 match only
u8* gt2_main_memcpy(u8* dest, u8* src, s32 len)
{
    u8* cur;
    int i = len - 1;
    
    if (src == dest)
        return dest;

    for (cur = dest; i != -1; i--)
        *cur++ = *src++;
    
    return dest;
}