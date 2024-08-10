#include "common.h"

char * gt2_ovr0_strchr (char *arg0, int arg1)
{
  char temp_v0;

  temp_v0 = *arg0;
  if (temp_v0 == 0)
    {
      return NULL;
    }
  if ((arg1 ^ temp_v0) & 0xFF)
    {
      return gt2_ovr0_strchr (arg0 + 1, arg1);
    }
  return arg0;
}
