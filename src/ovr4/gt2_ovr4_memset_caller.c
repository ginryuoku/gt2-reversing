#include "common.h"

u32 gt2_memset(u32*, u32, u32);                                 /* extern */

void gt2_ovr4_memset_caller(u32* arg0) {
    gt2_memset(arg0, -1, 0x17E8);
}
