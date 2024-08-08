#include "common.h"

void gt2_main_task0b20 (int *, int *, int);    /* extern */
void gt2_main_task0b21 (int *, int, int, int); /* extern */
extern int D_801E2CE0;
extern int D_801E2CF0;

void
gt2_main_task0b2 (void)
{
  gt2_main_task0b20 (&D_801E2CE0, &D_801E2CF0, 0x200);
  gt2_main_task0b21 (&D_801E2CE0, 0xF7, 0, 1);
}