// only builds with 2.8.1
#include "common.h"

void gt2_main_shared_arcaderace_funcF0(u8*, s32);        /* extern */

void gt2_main_shared_arcaderace_funcF(u16 arg0[]) {
    gt2_main_shared_arcaderace_funcF0(arg0 + 2, -1);
    arg0[25] = 0;
    arg0[22] = (u16) (arg0[22] | 0x80);
}
