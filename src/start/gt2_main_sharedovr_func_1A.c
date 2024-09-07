#include "common.h"

void gt2_main_sharedovr_func_19_0(s32);                /* extern */
s32 gt2_main_task020_callback_checker(s32);         /* extern */

void gt2_main_sharedovr_func_1A(void* arg0[]) {
    s32 temp_v0;

    temp_v0 = gt2_main_task020_callback_checker(0);
    arg0[3] = 0;
    arg0[4] = -1;
    gt2_main_sharedovr_func_19_0(arg0 + 0x3);
    gt2_main_task020_callback_checker(temp_v0);
}
