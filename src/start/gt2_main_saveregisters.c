// Thanks to nenkai for the solve!
#include "common.h"
#include "structs.h"

s32 gt2_main_saveregisters(gt2_saved_registers* registers) {

    // Can't use input operands here. 'more than 10 operands in `asm'
    __asm
    (
        "sw $ra, 0($a0)\n"  // registers->ra = $ra
        "sw $sp, 4($a0)\n"  // registers->sp = $sp
        "sw $s8, 8($a0)\n"  // registers->fp = $fp
        "sw $s0, 12($a0)\n" // s0 -> s7...
        "sw $s1, 16($a0)\n" 
        "sw $s2, 20($a0)\n"
        "sw $s3, 24($a0)\n"
        "sw $s4, 28($a0)\n"
        "sw $s5, 32($a0)\n"
        "sw $s6, 36($a0)\n"
        "sw $s7, 40($a0)\n"
        "sw $gp, 44($a0)\n" // registers->gp = $gp
    );

    return 0;
}
