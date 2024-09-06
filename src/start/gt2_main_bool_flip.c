#include "common.h"

extern void gt2_main_bool_func0();                            /* extern */
extern s32 D_801C93B0;

void gt2_main_bool_flip(void) {
    if (D_801C93B0 == 0) {
        D_801C93B0 = 1;
        gt2_main_bool_func0();
    }
}
