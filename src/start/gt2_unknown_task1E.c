// thanks to karas84 for the solve!
#include "common.h"

typedef struct {
    u8 pad1[80];
    s32 unk1;
    u8 pad2[8];
    u16 unk2; 
} Unk;

extern Unk D_801F0510[];

s32 gt2_unknown_task1E(void) {
#ifdef MATCHING
    register Unk *ptr asm("a0");
#else
    Unk *ptr;
#endif
    ptr = D_801F0510;
    return ptr->unk1 + (ptr->unk2 << 11);
}
