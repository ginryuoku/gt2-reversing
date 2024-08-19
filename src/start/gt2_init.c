#include "common.h"

void gt2_init_task0();                                 /* extern */
void gt2_sysinit();                                    /* extern */

void gt2_init(void) {
    gt2_init_task0();
    gt2_sysinit();
}
