// only builds with 2.8.1
#include "common.h"

void gt2_main_task20(s32, s32, s32, s32, s32, s32);             /* extern */
extern s32 D_80091174;

void gt2_main_task2(s32 arg0) {
    gt2_main_task20(arg0, *((arg0) + &D_80091174), 0, 0, 0, 0);
}
