#include "common.h"

unsigned int gt2_memset(unsigned int*, unsigned int, unsigned int);                   /* extern */
extern unsigned int D_800A8D5C;
extern unsigned int D_801C93B0;

void gt2_sysinit_task0(void) {
    gt2_memset(&D_800A8D5C, 0, (unsigned int) &D_801C93B0 - (unsigned int) &D_800A8D5C);
    return;
}
