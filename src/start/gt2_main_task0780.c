#include "common.h"

void gt2_main_task07800();                             /* extern */
extern u32 D_80090630;

void gt2_main_task0780(u32** arg0) {
    *arg0 = &D_80090630;
    gt2_main_task07800();
}
