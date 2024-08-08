#include "common.h"
void gt2_main_task2001 (int *, int, int); /* extern */

extern int arg0[0x16C];

int * gt2_main_task0800 (int *arg0, int arg1)
{
  if (arg0[90] != arg1)
    {
      arg0[90] = arg1;
      gt2_main_task2001 (&arg0[91], arg1, 0x800);
    }
  return &arg0[91];
}
