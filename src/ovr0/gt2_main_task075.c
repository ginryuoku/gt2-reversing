// Thanks to Nenkai for the solve.
#include "common.h"
typedef struct
{
    int _0x00;
    int _pad;
    int _0x08;
    char _0x0C[10];
    signed short _0x16;
} arg0_task075_sub;

typedef struct {
    char pad0[0x38];
    arg0_task075_sub unk_sub_0x38;
    signed short pad;
    char pad1[0x1e];
    signed short unk70;
    signed short unk72;
} arg0_task075;

void gt2_main_task0740(arg0_task075_sub*);        /* extern */
void gt2_main_task0750(arg0_task075_sub*, signed short*);  /* extern */

void gt2_main_task075(arg0_task075* arg0) {
    arg0->unk70 = 0;
    arg0->unk72 = 1;
    gt2_main_task0740(&arg0->unk_sub_0x38);
    gt2_main_task0750(&arg0->unk_sub_0x38, &arg0->unk70);
}
