#include "common.h"

void func_800686C8();                                  /* extern */
void func_80079DBC();                                  /* extern */
void func_80079E2C();                                 /* extern */
void func_80079E64();                                  /* extern */
void func_80079EEC(int);                                 /* extern */
void func_80079EF8(int);                                 /* extern */
void func_8007A0E0(int);                                 /* extern */
void func_8007A104(int, int);                              /* extern */
void func_8007C43C();                                  /* extern */
void gt2_sysinit_task00_dma_vsync();                                  /* extern */
void func_8007E8A0();                                  /* extern */
void func_8007F830(int);                                 /* extern */
void func_8007F924();                                  /* extern */
void func_800804F8();                                  /* extern */
void gt2_main_task07();                                /* extern */
void gt2_main_task08_play_music_a440(int);              /* extern */
void gt2_main_task09();                                /* extern */
void gt2_main_task0a_ovr_entrypoint();                 /* extern */
void gt2_main_task0b();                                /* extern */
extern int D_80011D38;

void gt2_main_task0(void) {
    gt2_sysinit_task00_dma_vsync();
    func_80079DBC();
    func_80079E2C(0x3C);
    func_80079E64();
    func_80079EEC(0x3C);
    func_80079EF8(4);
    func_8007A0E0(1);
    func_800686C8();
    func_8007C43C();
    func_8007F924();
    func_8007E8A0();
    func_800804F8();
    gt2_main_task07();
    gt2_main_task08_play_music_a440((int*)&D_80011D38);
    gt2_main_task09();
    gt2_main_task0a_ovr_entrypoint();
    gt2_main_task0b();
    func_8007A104(0xFFF, 0xFFF);
    func_8007F830(1);
}
