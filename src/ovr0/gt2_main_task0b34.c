// builds only with GCC 2.8.1
#include "common.h"

extern int gt2_memset (int *, int, int); /* extern */

typedef struct
{
  int pad0[16];
  int unk40;
} unkstruct_arg0_0b34;

void gt2_main_task0b34 (unkstruct_arg0_0b34 *arg0)
{
  gt2_memset (arg0, 0, 0x160);
  arg0->unk40 = 1;
}
