// thanks to karas84 for the solve!
// (karas84 solved max3, giving me the solution for the counterpart)
// builds only on 2.8.1
#include "common.h"

s32 gt2_ovr5_min3(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 < arg1) {
        if (arg2 < arg0) {
            return arg2;
        }
    } else {
        if (arg2 < arg1) {
            return arg2;
        }
        return arg1;
    }
    return arg0;
}
