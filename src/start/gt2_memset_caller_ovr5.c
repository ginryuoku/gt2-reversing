#include "common.h"

u32 gt2_memset(u32*, u32, u32);                         /* extern */

void gt2_memset_caller_ovr5(u32* arg0) {
    gt2_memset(arg0, 0, 0x94);
}
