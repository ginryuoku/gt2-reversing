// Thanks to nenkai for the solve!
#include "common.h"
#include "structs.h"

extern unsigned char gt2_vol_buffer[280 * 0x800]; // gt2_vol_buffer - This is used as a buffer. first for the vol header, then for the vol entries
extern unsigned char gt2_vol_header_ptr[24 * 0x800];  // gt2_vol_header_ptr - points to gt2_gtfs_header structure
extern int D_801E3604; // D_801E35F0 + 0x14 = offset of file infos

void gt2_main_cd_read(unsigned char* data, int sector_offset, int size);  /* extern */
void gt2_ovr0_vol_build_file_indices_cache();                              /* extern */ // gt2_main_vol_assign_file_indices_unk

void gt2_ovr0_vol_gtfs_init(void) { // gt2_main_vol_gtfs_init
    gt2_main_cd_read(gt2_vol_buffer, 0, sizeof(gt2_vol_buffer)); // gt2_main_cd_read(u8* data, sector_offset lba, int size);

    // copy vol header from vol buffer into header buffer
    memcpy(&gt2_vol_header_ptr, (void*)gt2_vol_buffer, sizeof(gt2_vol_header_ptr));

    // copy vol file entries into vol buffer (using count in header)
    memcpy(gt2_vol_buffer, (void*)gt2_vol_buffer + (D_801E3604 & 0xFFFFF800), sizeof(gt2_vol_buffer));
    
    gt2_ovr0_vol_build_file_indices_cache(); // gt2_main_vol_assign_file_indices_unk
}
