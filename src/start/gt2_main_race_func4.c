#include "common.h"

char* gt2_main_strcpy_slim(char*, const char*);      /* extern */

void gt2_main_race_func4(s32 arg0, s32 arg1, const char* arg2) {
    if (arg1 < 8U) {
        gt2_main_strcpy_slim((arg1 * 0x14) + arg0 + 0xC, arg2);
    }
}
