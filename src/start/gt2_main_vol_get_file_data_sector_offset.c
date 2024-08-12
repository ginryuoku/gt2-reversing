// Thanks to Nenkai and TheLeonix for the solve!
#include "common.h"
#include "structs.h"

extern char gt2_vol_header_ptr[24 * 0x800];

unsigned int gt2_main_vol_get_file_data_sector_offset(int file_data_index) { // gt2_main_vol_get_file_data_sector_offset
    char *gtfs_header = gt2_vol_header_ptr;
    unsigned int packed_value = ((unsigned int*)(gtfs_header + 0x10))[file_data_index];
    return GTFS_SECTOR_OFFSET(packed_value);
}
