// thanks to mono21400 for removing the redundant do{} and finding the volatile int
#include "common.h"

extern void VSyncCallback(int*);                                /* extern */
extern volatile int D_80011DF4;
extern int gt2_vsync_handler;

void gt2_sysinit_vsync_setup(void) {
    VSyncCallback(&gt2_vsync_handler);
    while (D_80011DF4 < 4);
    VSyncCallback(NULL);
}
