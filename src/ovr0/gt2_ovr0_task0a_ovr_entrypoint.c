// Builds only with GCC 2.8.1
#include "common.h"

extern void gt2_ovr0_task0a_ovr_func0(int*);                    /* extern */
extern int D_801EF610;

void gt2_ovr0_task0a_ovr_entrypoint(void) {
    gt2_ovr0_task0a_ovr_func0(&D_801EF610);
}
