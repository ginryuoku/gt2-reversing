#include "common.h"

typedef struct {
    char padding1[0x28];
    char pad1[0x22];
    char pad2[0x22];
} gt2_input_struct;

void CdInit();                                         /* extern */
void DecDCTReset(int);                                   /* extern */
void InitCARD(int);                                      /* extern */
void PadInitDirect(char*, char*);                      /* extern */
void ResetCallback();                                  /* extern */
void StartCARD();                                      /* extern */
void _bu_init();                                       /* extern */
void gt2_sysinit_gpu_setup();                          /* extern */
void gt2_sysinit_gte_setup();                          /* extern */
void gt2_sysinit_spu_setup();                          /* extern */
void gt2_sysinit_sysclock_setup();                     /* extern */
void gt2_sysinit_task0();                              /* extern */
void gt2_sysinit_vsync_setup();                        /* extern */
extern gt2_input_struct D_801F0C70;

void gt2_sysinit(void) {
    gt2_input_struct * ptr = &D_801F0C70;
    gt2_sysinit_task0();
    ResetCallback();
    gt2_sysinit_vsync_setup();
    CdInit();
    gt2_sysinit_spu_setup();
    InitCARD(0);
    StartCARD();
    _bu_init();
    PadInitDirect(ptr->pad1, ptr->pad2);
    gt2_sysinit_gpu_setup();
    DecDCTReset(0);
    gt2_sysinit_gte_setup();
    gt2_sysinit_sysclock_setup();
}