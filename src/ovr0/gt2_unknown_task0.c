#include "common.h"

int gt2_unknown_task0(char* arg0) {
    int var_a1;
    char temp_v1;
    char* var_a0;

    var_a0 = arg0;
    var_a1 = 0;
    do {
        temp_v1 = var_a0[6];
        if (!(temp_v1 & 1)) {
            var_a1 += 1;
        }
        var_a0 += 0x20;
    } while (!(temp_v1 & 0x80));
    return var_a1;
}
