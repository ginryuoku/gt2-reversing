// builds only with GCC 2.8.1
#include "common.h"

void gt2_main_task0b110(unsigned short);                          /* extern */
extern unsigned short D_801E2EF0;

void gt2_main_task0b11(unsigned int arg0) {
    gt2_main_task0b110(*((arg0) + &D_801E2EF0));
}
