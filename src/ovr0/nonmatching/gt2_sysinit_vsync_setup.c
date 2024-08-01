#include "common.h"

extern void VSyncCallback(void*);                                /* extern */
extern int D_80011DF4;
extern void gt2_vsync_handler;

void gt2_sysinit_vsync_setup(void) {
    VSyncCallback(&gt2_vsync_handler);
    do {

    } while (D_80011DF4 < 4);
    VSyncCallback(NULL);
}
