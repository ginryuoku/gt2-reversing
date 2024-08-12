// Thanks to Nenkai and TheLeonix for the solve!
#include "common.h"

extern char D_801E35F0[24 * 0x800];

#define GTFS_SECTOR_OFFSET(packed_value) (packed_value >> 11)

unsigned int gt2_main_vol_get_file_data_sector_offset(int file_data_index) { // gt2_main_vol_get_file_data_sector_offset
    char *gtfs_header = D_801E35F0;
    unsigned int packed_value = ((unsigned int*)(gtfs_header + 0x10))[file_data_index];
    return GTFS_SECTOR_OFFSET(packed_value);
}
