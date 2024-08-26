// builds only with GCC 2.8.1
#include "common.h"

void gt2_main_vol_get_file_data_sector_offset (int); /* extern */
extern unsigned short gt2_vol_cached_dir_indices[];

void
gt2_main_shared_arcaderace_func32 (int arg0)
{
  gt2_main_vol_get_file_data_sector_offset (gt2_vol_cached_dir_indices[arg0]);
}
