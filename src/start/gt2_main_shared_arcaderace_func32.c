// builds only with GCC 2.8.1
#include "common.h"

void gt2_main_vol_get_file_data_sector_offset (int); /* extern */
extern unsigned short D_801E2EF0;

void
gt2_main_shared_arcaderace_func32 (int arg0)
{
  gt2_main_vol_get_file_data_sector_offset (*((arg0) + &D_801E2EF0));
}
