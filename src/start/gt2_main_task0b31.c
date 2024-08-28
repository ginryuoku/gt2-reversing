// thanks to karas84 for the solve!
// only compiles on 2.8.1
#include "common.h"

void gt2_main_task0b31(s32* arg0) {
    s32 i;

    arg0[0] = -1;
    
    for (i = 0; i < 4; i++) {
        arg0[i + 1] = -1;
    }
    
    ((s16 *)arg0)[8] = 0;
}
