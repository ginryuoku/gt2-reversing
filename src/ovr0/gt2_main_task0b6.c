#include "common.h"

typedef struct {
    char unk0;
    char unk1;
    char unk2;
    char unk3;
    int unk4;
    int unk8;
    short unkC;
    short unkE;
    char unk10;
} unkstruct_801EF5F0;

extern unkstruct_801EF5F0 D_801EF5F0;

void gt2_main_task0b6(void) {
    D_801EF5F0.unk0 = 0;
    D_801EF5F0.unk1 = 0;
    D_801EF5F0.unk2 = 0;
    D_801EF5F0.unk8 = 0;
    D_801EF5F0.unkC = -1;
    D_801EF5F0.unkE = 0;
    D_801EF5F0.unk10 = 0;
}
