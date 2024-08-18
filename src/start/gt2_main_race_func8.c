// Thanks to Nenkai for the solve!
// compiles only in 2.8.1 (2.95.2 has wildly different codegen)
// suspicion: this may be race grid-related
#include "common.h"

typedef struct {
    u8 pad[0x88];
    u8 unk88[6];
    u8 unk8E[6];
} struct_race_func8;

void gt2_main_race_func8(struct_race_func8* arg0) {
    int i;
    for (i = 0; i < 6; i++)
        arg0->unk88[i] += arg0->unk8E[i];
}
