// thanks to karas84 for the solve!
// builds only on 2.8.1
#include "common.h"

s32 gt2_ovr3_max3(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 < arg0) {
        if (arg0 < arg2) {
            return arg2;
        }
    } else {
        if (arg1 < arg2) {
            return arg2;
        }
        return arg1;
    }
    return arg0;
}
