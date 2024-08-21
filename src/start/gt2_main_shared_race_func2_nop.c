// thanks to karas84 for the solve
#include "common.h"

void gt2_main_shared_race_func2_nop(void) {
    // likely has some kind of debug guard or something that 
#ifdef MATCHING
    int b[4];
    asm("");
#endif
    return;
}
