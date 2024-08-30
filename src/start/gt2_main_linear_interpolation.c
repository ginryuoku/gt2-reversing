// thanks to Nenkai for the solve1
// works only on 2.8.1 with no divide-by-zero check
#include "common.h"

// gt2_main_linear_interpolation
s32 gt2_main_linear_interpolation(s32 val, s32 x0, s32 x1, s32 y0, s32 y1) {
    if (x0 < 0) 
        return -1;
    
    if (x0 >= val) 
        return y0;
    
    if (val >= x1)
        return y1;

    return y0 + (y1 - y0) * (val - x0) / (x1 - x0);
}
