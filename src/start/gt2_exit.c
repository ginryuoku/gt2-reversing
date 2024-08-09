// also a hideous function, but SquareMan of the PS1/PS2 decomp discord cracked it
#include "common.h"

extern __attribute ((noreturn)) void _exit (int); /* extern */
extern void gt2_exit_task0 ();                            /* static */

__attribute ((noreturn)) void
gt2_exit (int arg0)
{
  gt2_exit_task0();
  _exit (arg0);
}
