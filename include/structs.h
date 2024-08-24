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

typedef struct
{
  int field_0;
  int field_4;
  signed char field_8;
  unsigned char field_9;
  unsigned char field_A;
  signed char field_B;
  unsigned char field_C;
  unsigned char field_D;
  signed char field_E;
  unsigned char field_F;
  unsigned char field_10;
  unsigned char field_11;
  unsigned char field_12;
  unsigned char field_13;
  unsigned char field_14;
  signed char field_15;
  unsigned char field_16;
  unsigned char field_17;
  int field_18;
  signed char field_1C;
  unsigned char field_1D;
  unsigned char field_1E;
  signed char field_1F;
  unsigned char field_20;
  unsigned char field_21;
  signed char field_22;
  signed char field_23;
  signed char field_24;
  signed char field_25;
  signed char field_26;
  unsigned char field_27;
  signed char field_28;
  signed char field_29;
  signed char field_2A;
  signed char field_2B;
  signed char field_2C;
  signed char field_2D;
  unsigned char field_2E;
  unsigned char field_2F;
  unsigned char field_30;
  signed char field_31;
  signed char field_32;
  signed char field_33;
  signed char field_34;
  unsigned char field_35;
  signed char field_36;
  signed char field_37;
  signed char field_38;
  signed char field_39;
  signed char field_3A;
  signed char field_3B;
  unsigned char field_3C;
  signed char field_3D;
  signed char field_3E;
  signed char field_3F;
  signed char field_40;
  signed char field_41;
  signed char field_42;
  unsigned char field_43;
  signed char field_44;
  signed char field_45;
  signed char field_46;
  unsigned char field_47;
  signed char field_48;
  signed char field_49;
  signed char field_4A;
  signed char field_4B;
} gt2_race_part0;

typedef struct
{
  int field_0;
  int field_4;
  int field_8;
} gt2_race_part1;

typedef struct
{
  int field_0;
  int field_4;
  signed char field_8;
  unsigned char field_9;
  signed char field_A;
  signed char field_B;
  signed char field_C;
  unsigned char field_D;
  signed char field_E;
  signed char field_F;
} gt2_race_part_2;


typedef struct
{
  int field_0;
  int field_4;
  signed char field_8;
  unsigned char field_9;
  signed char field_A;
  signed char field_B;
  signed char field_C;
  unsigned char field_D;
  signed char field_E;
  signed char field_F;
} gt2_race_part2;

typedef struct
{
  int field_0;
  int field_4;
  int field_8;
  int field_C;
  int field_10;
  int field_14;
  int field_18;
  int field_1C;
  int field_20;
  int field_24;
  int field_28;
  int field_2C;
  int field_30;
  int field_34;
  int field_38;
  int field_3C;
} gt2_race_part3_2;

typedef struct
{
  int field_0;
  int field_4;
} gt2_race_part3_3;

typedef struct
{
  int field_0;
  int field_4;
  int field_8;
  int field_C;
  int field_10;
  int field_14;
  int field_18;
  int field_1C;
  int field_20;
  int field_24;
  int field_28;
  int field_2C;
  int field_30;
  int field_34;
  int field_38;
  int field_3C;
} gt2_race_part4_2;

typedef struct
{
  int field_0;
  int field_4;
  signed char field_8;
  unsigned char field_9;
  signed char field_A;
  signed char field_B;
  signed short field_C[4];
  signed short field_14;
  signed short field_16;
  signed short field_18;
  signed short field_1A;
  signed short field_1C;
  signed short field_1E;
  unsigned char field_20;
  signed char field_21;
  unsigned char field_22;
  unsigned char field_23;
} gt2_race_part_gear;

typedef struct
{
  int field_0;
  int field_4;
  int field_8;
  int field_C;
} gt2_race_part7;

typedef struct
{
  int field_0;
  int field_4;
  int field_8;
} gt2_race_part8;

typedef struct
{
  int field_0;
  int field_4;
  int field_8;
} gt2_race_part9;

typedef struct
{
  int field_0;
  int field_4;
  int field_8;
} gt2_race_part10;

typedef struct
{
  int field_0;
  int field_4;
  int field_8;
} gt2_race_part11;

typedef struct
{
  int field_0;
  int field_4;
  int field_8;
} gt2_race_part12;

typedef struct
{
  int field_0;
  int field_4;
  int field_8;
} gt2_race_part13;

typedef struct
{
  int field_0;
  int field_4;
  int field_8;
} gt2_race_part14;

typedef struct
{
  int field_0;
  int field_4;
  int field_8;
  int field_C;
  int field_10;
} gt2_race_part15;

typedef struct entry16
{
  int field_0;
  int field_4;
  int field_8;
} gt2_race_part16;

typedef struct
{
  int field_0;
  int field_4;
  int field_8;
} gt2_race_part17;

typedef struct
{
  int field_0;
  int field_4;
  int field_8;
} gt2_race_part18;

typedef struct
{
  int field_0;
  int field_4;
  int field_8;
  int field_C;
  unsigned char field_10;
  unsigned char field_11;
  signed char field_12;
  unsigned char field_13;
  unsigned char field_14;
  signed char field_15;
  signed char field_16;
  signed char field_17;
  int field_18;
} gt2_race_part19;

typedef struct
{
  int field_0;
  int field_4;
  signed char field_8;
  signed char field_9;
  signed char field_A;
  signed char field_B;
  unsigned char field_C;
  unsigned char field_D;
  signed char field_E;
  signed char field_F;
} gt2_race_part20;

typedef struct
{
  int field_0;
  int field_4;
  int field_8;
  signed char field_C;
  unsigned char field_D;
  unsigned char field_E;
  signed char field_F;
} gt2_race_part21;

typedef struct
{
  int field_0;
  int field_4;
  int field_8;
  signed char field_C;
  signed char field_D;
  signed char field_E;
  signed char field_F;
  signed char field_10;
  signed char field_11;
  signed char field_12;
  signed char field_13;
  signed char field_14;
  signed char field_15;
  signed char field_16;
  signed char field_17;
  unsigned char field_18;
  unsigned char field_19;
  signed char field_1A;
  signed char field_1B;
  signed char field_1C;
  signed char field_1D;
  signed char field_1E;
  signed char field_1F;
} gt2_race_part22;

typedef struct
{
  int field_0;
  int field_4;
  int field_8;
  int field_C;
  int field_10;
  int field_14;
} gt2_race_part23;

typedef struct
{
  int field_0;
  int field_4;
  int field_8;
  int field_C;
  int field_10;
} gt2_race_part24;

typedef struct
{
  int field_0;
  int field_4;
  int field_8;
  int field_C;
  int field_10;
  int field_14;
  int field_18;
  int field_1C;
  int field_20;
  int field_24;
  int field_28;
  int field_2C;
  int field_30;
  int field_34;
  int field_38;
  int field_3C;
  int field_40;
  int field_44;
  int field_48;
} gt2_race_part25;

typedef struct
{
  int field_0;
  int field_4;
  int field_8;
  int field_C;
} gt2_race_part26;

typedef struct
{
  unsigned short field_0;
  unsigned short field_2;
  unsigned short field_4;
  unsigned short field_6;
  unsigned short field_8;
  unsigned short field_A;
  unsigned short field_C;
  unsigned short field_E;
  unsigned short field_10;
  unsigned short field_12;
  unsigned short field_14;
  unsigned short field_16;
  unsigned short field_18;
  unsigned short field_1A;
  unsigned short field_1C;
  unsigned short field_1E;
  unsigned short field_20;
  unsigned short field_22;
  unsigned short field_24;
  unsigned short field_26;
  unsigned short field_28;
  unsigned short field_2A;
  unsigned short field_2C;
  unsigned short field_2E;
  unsigned short field_30;
  unsigned short field_32;
  unsigned short field_34;
  unsigned short field_36;
  unsigned short field_38;
  char field_3A;
  char field_3B;
  unsigned short gear_ratios[8];
  unsigned short gear_max_final_drive_ratio;
  unsigned char gear_auto_setting;
  char field_4F;
  unsigned char field_50;
  unsigned char field_51;
  unsigned char field_52;
  unsigned char field_53;
  char field_54;
  char field_55;
  char field_56;
  char field_57;
  char field_58;
  char field_59;
  unsigned char field_5A;
  unsigned char field_5B;
  unsigned char field_5C;
  unsigned char field_5D;
  unsigned char field_5E;
  unsigned char field_5F;
  unsigned char field_60;
  unsigned char field_61;
  char field_62;
  char field_63;
  unsigned char field_64;
  char field_65;
  unsigned char field_66;
  char field_67;
  unsigned char field_68;
  char field_69;
  unsigned char field_6A;
  char field_6B;
  unsigned char field_6C;
  unsigned char field_6D;
  char field_6E;
  unsigned char field_6F;
  char field_70;
  char field_71;
  char field_72;
  char field_73;
  unsigned char field_74;
  unsigned char field_75;
  char field_76;
  char field_77;
  signed short field_78;
  char field_7A;
  char gear_auto_setting_current;
  signed short gear_max_final_drive_ratio_current;
  unsigned short field_7E;
  unsigned short field_80;
  signed char gap82[1542];
  int entries5_1[2];
  unsigned char gap690[760];
  gt2_race_part0 entries0[4];
  int entries0_1[4];
  gt2_race_part1 entries1[2];
  int entries1_1[2];
  gt2_race_part2 entries2[2];
  int entries2_1[2];
  unsigned char gapB10[160];
  int entries3[0];
  int entries3_1[10];
  unsigned char gapBB8[40];
  gt2_race_part3_2 entries3_2[10];
  gt2_race_part3_3 entries3_3[25];
  int entries4_1[10];
  int entries4_1__[10];
  gt2_race_part4_2 entries4_2[10];
  gt2_race_part_gear entries6[4];
  int entries6_1[4];
  gt2_race_part7 entries7[4];
  int entries7_1[4];
  gt2_race_part8 entries8[4];
  int entries8_1[4];
  gt2_race_part9 entries9[2];
  int entries9_1[2];
  gt2_race_part10 entries10[2];
  int entries10_1[2];
  gt2_race_part11 entries11[2];
  int entries11_1[2];
  gt2_race_part12 entries12[2];
  int entries12_1[2];
  gt2_race_part13 entries13[4];
  int entries13_1[4];
  gt2_race_part14 entries14[2];
  int entries14_1[2];
  gt2_race_part15 entries15[5];
  int entries15_1[5];
  gt2_race_part16 entries16[3];
  int entries16_1[3];
  gt2_race_part17 entries17[4];
  int entries17_1[4];
  gt2_race_part18 entries18[4];
  int entries18_1[4];
  gt2_race_part19 entries19[5];
  int entries19_1[5];
  gt2_race_part20 entries20[2];
  int entries20_1[2];
  gt2_race_part21 entries21[2];
  int entries21_1[2];
  gt2_race_part22 entries22[6];
  int entries22_1[6];
  gt2_race_part23 entries23[1];
  int entries23_1[1];
  gt2_race_part24 entries24[1];
  int entries24_4;
  gt2_race_part25 entries25[1];
  int entries25_1[1];
  gt2_race_part26 entries26[1];
  int entries26_1[1];
  int indices[27];
} gt2_race_entry;

typedef enum
{
    GT2_PART_TYPE_GEAR = 6,
} gt2_race_part_type;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} struct_1c945c;

typedef struct
{
    int ra;
    int sp;
    int fp;
    int s0;
    int s1;
    int s2;
    int s3;
    int s4;
    int s5;
    int s6;
    int s7;
    int gp;
} gt2_saved_registers;

typedef struct {
    short pad0[0xBD8];
    short unk17B0;
    short unk17B2;
    short unk17B4;
    short pad1[0x3];
    short unk17BC;
    short pad2[0xD];
    short unk17D8;
    short unk17DA;
    short unk17DC;
} struct_race_setter;
