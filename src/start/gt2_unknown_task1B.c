// only builds on 2.8.1
#include "common.h"

extern s32* D_80095ABC;

s32 gt2_unknown_task1B(s32 arg0) {
    return *((arg0 * 3) + D_80095ABC);
}
