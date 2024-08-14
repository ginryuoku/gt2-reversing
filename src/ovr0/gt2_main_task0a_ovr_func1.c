// builds only with GCC 2.8.1
#include "common.h"

typedef int s32;
extern char* D_800A8E5C;// = "gt2.ovl";

extern s32* gt2_main_task082_file_loader();                           /* extern */

s32* gt2_main_task0a_ovr_func1(s32 arg0) {
    return gt2_main_task082_file_loader(&D_800A8E5C, arg0);
}
