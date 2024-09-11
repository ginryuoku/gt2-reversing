#include "common.h"

extern void gt2_main_bool_flip();                             /* extern */
extern void gt2_ovr0_task0();                                 /* extern */
extern void gt2_main_task1();                                 /* extern */
extern void gt2_load_overlay_default(int);                                /* extern */

int gt2_main(void) {
    gt2_main_bool_flip();
    gt2_ovr0_task0();
    gt2_main_task1();
    gt2_load_overlay_default(1);
    return 0;
}
