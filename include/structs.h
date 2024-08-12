typedef struct {
    int *unk0;
    int ptr_table[0x10];
    char vendorBootLogo[0x10];
    char CD001[0x8];
    char _11DA0[0x4];
    char gt2vol[0x8];
    char musicdat[0xc];
    char streamdat[0xc];
    char carobj[0x8];
    char carlogo[0xc];
} rodata_ovr0;

typedef struct {
    int date_time;
    unsigned short next_dir_or_file_index;
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

typedef struct {
    char padding1[0x28];
    char pad1[0x22];
    char pad2[0x22];
} gt2_input_struct;
