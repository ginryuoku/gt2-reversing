// only compiles with 2.8.1
#include "common.h"

// TODO: this struct is almost certainly a stub
typedef struct {
    u32 pad0;
    s32 unk4;
} struct_race_func7;

u32 gt2_memset(u32*, u32, u32);                         /* extern */

void gt2_main_race_func7(struct_race_func7* arg0) {
    gt2_memset(arg0, 0, 0xC);
    arg0->unk4 = -1;
}
