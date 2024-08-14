// builds only with GCC 2.8.1
#include "common.h"

extern void gt2_main_task0c_gpu_reg1_op(int);                   /* extern */
extern int D_80011DF4;

void gt2_vsync_handler(void) {
    gt2_main_task0c_gpu_reg1_op(1);
    D_80011DF4 += 1;
}
