#include "common.h"

typedef struct {
    short unk0;
    short pad0[0x12];
    short unk26;
    short pad1[0x8];
    short unk38;
} struct_func21;

void gt2_main_race_func21(struct_func21* arg0) {
    arg0->unk26 = -1;
    arg0->unk38 = (s16) (arg0->unk0 + 0x44);
}
