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
    short count1;
    short count2;
    unsigned int reserved;
    unsigned int field_10;
    unsigned int field_14;
} gt2_gtfs_header;

extern unsigned char D_800A97D0[0x8C000]; // gt2_vol_buffer - This is used as a buffer. first for the vol header, then for the vol entries
extern unsigned char D_801E35F0[0xC000];  // gt2_vol_header_ptr - points to gt2_gtfs_header structure
extern int D_801E3604; // D_801E35F0 + 0x14 = offset of file infos

void gt2_main_cd_read(unsigned char* data, int sector_offset, int size);  /* extern */
void gt2_ovr0_vol_assign_file_indices_unk();                              /* extern */ // gt2_main_vol_assign_file_indices_unk

void gt2_ovr0_vol_gtfs_init(void) { // gt2_main_vol_gtfs_init
    gt2_main_cd_read(D_800A97D0, 0, sizeof(D_800A97D0)); // gt2_main_cd_read(u8* data, sector_offset lba, int size);

    // copy vol header from vol buffer into header buffer
    memcpy(&D_801E35F0, (void*)D_800A97D0, sizeof(D_801E35F0));

    // copy vol file entries into vol buffer (using count in header)
    memcpy(D_800A97D0, (void*)D_800A97D0 + (D_801E3604 & 0xFFFFF800), sizeof(D_800A97D0));
    
    gt2_ovr0_vol_assign_file_indices_unk(); // gt2_main_vol_assign_file_indices_unk
}
