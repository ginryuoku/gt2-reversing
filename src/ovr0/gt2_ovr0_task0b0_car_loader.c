#include "common.h"

extern void gt2_main_task0b00_path_sanitizer();               /* extern */
extern void gt2_main_task0b01_noop_loader();                  /* extern */
extern void gt2_ovr0_task0b02_carobj_loader();                /* extern */
extern void gt2_ovr0_task0b03_carlogo_loader();               /* extern */
extern void gt2_ovr0_task0b04_carwheel_loader();              /* extern */
extern void gt2_ovr0_task0b05_enginedata_loader();            /* extern */

void gt2_ovr0_task0b0_car_loader(void) {
    gt2_main_task0b00_path_sanitizer();
    gt2_main_task0b01_noop_loader();
    gt2_ovr0_task0b02_carobj_loader();
    gt2_ovr0_task0b03_carlogo_loader();
    gt2_ovr0_task0b04_carwheel_loader();
    gt2_ovr0_task0b05_enginedata_loader();
}
