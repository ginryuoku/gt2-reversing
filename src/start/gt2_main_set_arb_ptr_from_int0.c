// thanks to karas84 for the solve!
#include "common.h"

extern s32 D_80090A7C;

s32 *gt2_main_set_arb_ptr_from_int0(s32* arg0[], s32 arg1) {
    arg0[1] = &D_80090A7C;
    arg0[0] = arg1;
    return arg0;
}