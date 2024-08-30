// thanks to Nenkai and karas84 for the solve!
// compiles only on 2.8.1
#include "common.h"

extern s16 D_801C93B4; // gt2_carwheel_num_files
extern u16 D_801E2FC6; // file indices group 2 (car wheel)
extern s32 D_801E30F0[];

u32 gt2_main_shared_arcade_func0(u32 val) 
{
    s32 min = 0;
    s32 max = D_801C93B4;
    u32 mid;
    u32 idx;
    while (1)
    {
        mid = ((min + max) >> 1);
        idx = D_801E30F0[mid];
        if (val == D_801E30F0[mid])
            return D_801E2FC6+mid;

        if (min >= max)
            return D_801E2FC6;

        if (idx < val)
            min = mid + 1;
        else
            max = mid;
    }
}