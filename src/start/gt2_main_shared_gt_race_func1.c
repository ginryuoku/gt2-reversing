// thanks to Nenkai for solving this function
#include "common.h"

typedef struct
{
  char padding[0x60];
  char data[0x10];
} unkstruct_8005DB90;

unsigned int gt2_main_shared_gt_race_func1 (unkstruct_8005DB90 *arg0, int arg1)
{
  unsigned char temp_v0 = arg0->data[arg1 / 2];
  if (arg1 & 1)
    return temp_v0 >> 4;
  else
    return temp_v0 & 0x0F;
}
