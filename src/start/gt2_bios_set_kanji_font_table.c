#include "common.h"

u32 Krom2RawAdd(s16); // this isn't actually the correct signature for Krom2RawAdd
extern u32 D_801C9518;

// gt2_bios_set_kanji_font_table
void gt2_bios_set_kanji_font_table(void) {
    D_801C9518 = Krom2RawAdd(0x8140);
}
