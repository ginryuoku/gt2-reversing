#include "common.h"

extern void gt2_callback_double_buffer_flip();                                  /* extern */
extern void func_80085B3C(int*, char*, int*);                      /* extern */
extern char D_80011D84;
extern int D_801697D0;
extern int D_801F0CE0;

int* gt2_show_vendor_bootlogo_task0(void) {
    if (D_801697D0 == 0) {
        gt2_callback_double_buffer_flip();
        func_80085B3C(&D_801697D0, &D_80011D84, &D_801F0CE0);
    }
    return &D_801697D0;
}
