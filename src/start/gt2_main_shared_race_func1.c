// thanks to karas84 for the solve!
#include "common.h"

extern s32* D_801E18E0;

s32 *gt2_main_shared_race_func1(s32 arg0) {
    s32 *ptr = &D_801E18E0;
    // TODO: figure out a better way to express this pointer?
    return &ptr[arg0 * 6 + 2];
}
