#include "common.h"

typedef struct
{
  short unk0;
  int pad0[4100];
  int unk4014;
  short unk4018;
  char pad1;
  char unk401B;
} unkstruct_arg0_0b30;

void gt2_main_task0b30 (unkstruct_arg0_0b30 *arg0)
{
  arg0->unk4018 = -1;
  arg0->unk0 = 0;
  arg0->unk4014 = 0x2710;
  arg0->unk401B = 0;
}
