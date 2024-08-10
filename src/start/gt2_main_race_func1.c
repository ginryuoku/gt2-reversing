#include "common.h"

typedef struct
{
  int pad0[0x13];
  int unk4C;
  int unk50;
  int unk54;
} arg0_race_func1;

void
gt2_main_race_func1 (arg0_race_func1 *arg0, int arg1)
{
  arg0->unk50 = (arg0->unk50 + arg1);
  arg0->unk54 = (arg0->unk54 + 1);
  if (arg1 == 1)
    {
      arg0->unk4C = (arg0->unk4C + 1);
    }
}