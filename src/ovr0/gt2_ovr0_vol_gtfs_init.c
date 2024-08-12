// Thanks to nenkai for the solve!
#include "common.h"
typedef struct {
    int date_time;
    short next_dir_or_file_index;
    unsigned char  entry_flags; // 0x00 = file, 0x01 = dir, 0x80 = end of dir
    char name[25];
} gt2_vol_entry;

// https://problemkaputt.de/psxspx-cdrom-file-archive-gtfs-gran-turismo-2.htm
typedef struct
{
    unsigned int magic;
    unsigned int empty;
    unsigned short file_data_count;
    unsigned short file_entry_count;
    unsigned int reserved;
    // array of file offset (encoded int) 
    // - [0] is always refering to main header
    // - [1] is expected to be offset to file entries
    // - [2..] is where data starts
    // pad to 0x800
    // array of file entries (gt2_vol_entry)
    // pad to 0x800
    // data starts
} gt2_gtfs_header;

extern unsigned char gt2_vol_buffer[280 * 0x800]; // gt2_vol_buffer - This is used as a buffer. first for the vol header, then for the vol entries
extern unsigned char gt2_vol_header_ptr[24 * 0x800];  // gt2_vol_header_ptr - points to gt2_gtfs_header structure
extern int D_801E3604; // D_801E35F0 + 0x14 = offset of file infos

void gt2_main_cd_read(unsigned char* data, int sector_offset, int size);  /* extern */
void gt2_ovr0_vol_assign_file_indices_unk();                              /* extern */ // gt2_main_vol_assign_file_indices_unk

void gt2_ovr0_vol_gtfs_init(void) { // gt2_main_vol_gtfs_init
    gt2_main_cd_read(gt2_vol_buffer, 0, sizeof(gt2_vol_buffer)); // gt2_main_cd_read(u8* data, sector_offset lba, int size);

    // copy vol header from vol buffer into header buffer
    memcpy(&gt2_vol_header_ptr, (void*)gt2_vol_buffer, sizeof(gt2_vol_header_ptr));

    // copy vol file entries into vol buffer (using count in header)
    memcpy(gt2_vol_buffer, (void*)gt2_vol_buffer + (D_801E3604 & 0xFFFFF800), sizeof(gt2_vol_buffer));
    
    gt2_ovr0_vol_assign_file_indices_unk(); // gt2_main_vol_assign_file_indices_unk
}
