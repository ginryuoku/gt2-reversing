#include "common.h"

extern void gt2_callback_double_buffer_flip();                                  /* extern */
extern void gt2_main_flip_double_buffers(int *, char *, int *); /* extern */
extern char D_80011D84;
extern int D_801697D0;
extern int D_801F0CE0;

int* gt2_show_vendor_bootlogo_task0(void) {
    if (D_801697D0 == 0) {
        gt2_callback_double_buffer_flip();
        gt2_main_flip_double_buffers(&D_801697D0, &D_80011D84, &D_801F0CE0);
    }
    return &D_801697D0;
}
