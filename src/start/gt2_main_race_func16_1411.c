// compiles only on 2.95.2
#include "common.h"

void gt2_main_race_func16_1411(s32* arg0[], s32* arg1[]) {
    s32 var0;
    s32 var1;

    var0 = arg1[1];
    var1 = arg1[2];
    *arg0 = *arg1;
    arg0[1] = var0;
    arg0[2] = var1;
}
