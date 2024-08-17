#include "common.h"
#include "structs.h"

s32 (*gt2_main_saveregisters(s32*))(s32, s32, s32, s32); /* extern */
extern s32 D_801C942C;
extern struct_1c945c D_801C945C;

void gt2_main_task1(void) {
    s32 (*temp_v0)(s32, s32, s32, s32);

    temp_v0 = gt2_main_saveregisters(&D_801C942C);
    if (temp_v0 != NULL) {
        temp_v0(D_801C945C.unk0, D_801C945C.unk4, D_801C945C.unk8, D_801C945C.unkC);
    }
}
