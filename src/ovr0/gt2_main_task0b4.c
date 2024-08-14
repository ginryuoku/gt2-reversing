// builds only with GCC 2.8.1
#include "common.h"

extern int gt2_sysinit_task00(char*, int, int);

typedef struct {
    short unk0;
    short unk2;
} unkstruct_800A6F18;

extern unkstruct_800A6F18 D_800A6F18;
extern char D_801C98A0;

void gt2_main_task0b4(void) {
    gt2_sysinit_task00(&D_801C98A0, 0, 0x40);
    D_800A6F18.unk0 = -0x40;
    D_800A6F18.unk2 = 0x40;
}
