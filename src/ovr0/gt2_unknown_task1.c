// thanks to 1superchip for the solve!
#include "common.h"

typedef struct
{
  int pad0[0x20];
  int unk80;
  int unk84;
} arg0_unk_task1;

int gt2_unknown_task1 (arg0_unk_task1 *arg0)
{
  return arg0->unk80++ < arg0->unk84;
}
