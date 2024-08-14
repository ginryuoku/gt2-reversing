// builds only with GCC 2.8.1
#include "common.h"

extern int D_801C93C4;

typedef struct {
    unsigned short pad0[228];
    unsigned short unk1C8;
    unsigned short unk1CA;
} unkstruct_801E2EF0;

extern unkstruct_801E2EF0 D_801E2EF0;

void gt2_main_task0b7(void) {
    D_801C93C4 = (D_801E2EF0.unk1CA - D_801E2EF0.unk1C8) - 1;
}
