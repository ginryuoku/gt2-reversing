// Thanks to mkst for suggesting I check the default CFLAGS. this one
// requires -msplit-addresses to work.
#include "common.h"

// TODO: identify real struct and edit accordingly
typedef struct {
    int pad[0x16];
    int unk58;
    int unk5C;
} arg0_race_func2;

void gt2_main_race_func2(arg0_race_func2* arg0, int arg1) {
    int temp_v0_2;
    unsigned int temp_v0;

    temp_v0 = arg0->unk5C + arg1;
    arg0->unk5C = temp_v0;
    if (temp_v0 > 0x05F5E100U) {
        temp_v0_2 = arg0->unk58 + 1;
        arg0->unk58 = temp_v0_2;
        if (temp_v0_2 < 0) {
            arg0->unk58 = 0x7FFFFFFF;
        }
        arg0->unk5C = (unsigned int) (arg0->unk5C - 0x05F5E100);
    }
}
