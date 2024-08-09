#include "common.h"

void gt2_main_task0b10 ();         /* extern */
void gt2_main_task0b11 (unsigned int, unsigned int); /* extern */
extern unsigned int *D_801E18E0;

void
gt2_main_task0b1 (void)
{
  int var_a0;
  unsigned int idx;
  unsigned int *temp_v1;
  unsigned int *temp_v2;

  gt2_main_task0b10 ();
  gt2_main_task0b11 (6, &D_801E18E0);

  var_a0 = 8;

  temp_v1 = &D_801E18E0 + var_a0;
  temp_v2 = &D_801E18E0;

  for (idx = 0; idx < ((short)D_801E18E0[6]); ++idx)
    {
      var_a0 += 0x18;
      *temp_v1 += *temp_v2;
    }
}