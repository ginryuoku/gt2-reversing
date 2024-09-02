// Builds only with GCC 2.8.1
#include "common.h"

void gt2_main_task02();                                  /* extern */
void gt2_main_spu_mainvol_reset();                                  /* extern */
void gt2_main_spu_mainvol_reset_task0();                                 /* extern */
void gt2_main_task00();                                  /* extern */
void gt2_main_task01_setter(int);                                 /* extern */
void gt2_main_spu_task1(int);                                 /* extern */
void gt2_main_spu_ctrlregcpucnt_setter(int);                                 /* extern */
void gt2_main_spu_reverb_out_setter(int, int);                              /* extern */
void gt2_main_task03();                                  /* extern */
void gt2_sysinit_task00_dma_vsync();                                  /* extern */
void gt2_main_task05_sdkevent();                                  /* extern */
void gt2_main_task0c_gpu_reg1_op(int);                                 /* extern */
void gt2_main_task04_pad_config();                                  /* extern */
void gt2_bios_set_kanji_font_table();                                  /* extern */
void gt2_main_task07();                                /* extern */
void gt2_ovr0_task08_play_music_a440(int);              /* extern */
void gt2_ovr0_vol_gtfs_init();                                /* extern */
void gt2_ovr0_task0a_ovr_entrypoint();                 /* extern */
void gt2_ovr0_task0b();                                /* extern */
const char D_80011D38[] = "/";

void gt2_ovr0_task0(void) {
    gt2_sysinit_task00_dma_vsync();
    gt2_main_spu_mainvol_reset();
    gt2_main_spu_mainvol_reset_task0(0x3C);
    gt2_main_task00();
    gt2_main_task01_setter(0x3C);
    gt2_main_spu_task1(4);
    gt2_main_spu_ctrlregcpucnt_setter(1);
    gt2_main_task02();
    gt2_main_task03();
    gt2_main_task04_pad_config();
    gt2_main_task05_sdkevent();
    gt2_bios_set_kanji_font_table();
    gt2_main_task07();
    gt2_ovr0_task08_play_music_a440((int*)&D_80011D38);
    gt2_ovr0_vol_gtfs_init();
    gt2_ovr0_task0a_ovr_entrypoint();
    gt2_ovr0_task0b();
    gt2_main_spu_reverb_out_setter(0xFFF, 0xFFF);
    gt2_main_task0c_gpu_reg1_op(1);
}
