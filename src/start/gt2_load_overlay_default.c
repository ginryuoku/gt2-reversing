// only builds with 2.8.1
#include "common.h"

void gt2_load_overlay(s32, s32, s32, s32, s32, s32);             /* extern */
extern s32 D_80091174;

void gt2_load_overlay_default(s32 overlay) {
    gt2_load_overlay(overlay, *((overlay) + &D_80091174), 0, 0, 0, 0);
}
