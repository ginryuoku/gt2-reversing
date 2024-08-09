// a hideous function, but SquareMan of the PS1/PS2 decomp discord cracked it
#include "common.h"

extern int *D_800A7110;

typedef void (*UnkFunc) (void);

void
gt2_exit_task0 (void)
{
  while (*D_800A7110 != 0)
    {
      D_800A7110++;
      ((UnkFunc) * (D_800A7110 - 1)) ();
    }
}
