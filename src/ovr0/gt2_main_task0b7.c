// builds only with GCC 2.8.1
#include "common.h"

extern int D_801C93C4;
extern unsigned short gt2_vol_cached_dir_indices[];

void gt2_main_task0b7(void) {
    D_801C93C4 = (gt2_vol_cached_dir_indices[0xE5] - gt2_vol_cached_dir_indices[0xE4]) - 1;
}
