// thanks to karas84 for the solve!
#include "common.h"

extern s32 *D_801F0510[];

void gt2_main_task200112(void) {
#ifdef MATCHING
    register volatile u8 *ptr asm("a0");
#else
    volatile u8 *ptr;
#endif
    ptr = D_801F0510;
    // looks to be an IRQ spinlock?
    while(ptr[0x166]) {};
}