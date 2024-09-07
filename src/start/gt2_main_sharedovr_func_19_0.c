// builds only on 2.8.1
#include "common.h"

s32 gt2_main_task020_callback_checker(s32);         /* extern */

void gt2_main_sharedovr_func_19_0(void* arg0[]) {
    s32 temp_a0;

    temp_a0 = gt2_main_task020_callback_checker(0);
    arg0[2] = 0;
    arg0[3] = 0;
    arg0[4] = 0;
    arg0[5] = 0;
    gt2_main_task020_callback_checker(temp_a0);
}
