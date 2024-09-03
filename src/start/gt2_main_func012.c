#include "common.h"

s32 gt2_main_func012(s32 arg0) {
    s32 temp_a1;
    s32 temp_v0;
    s32 var_v0;

    temp_v0 = ((s32) ((arg0 & 0xFF00) + 0x2100) >> 1) ^ 0xA000;
    temp_a1 = arg0 & 0xFF;
    if (!(arg0 & 0x100)) {
        var_v0 = temp_v0 - 2;
    } else {
        var_v0 = (temp_v0 + 0x20) - (temp_a1 < 0x60);
    }
    return var_v0 + temp_a1;
}
