// Thanks to Nenkai for the structure and most of the solve,
// and thanks to karas84 for accepting the inevitable and inserting
// a nop to make GCC 2.8.1 (2.95.2 is a no-go) happy.
// Thanks also to Ethan for telling me about the static int padding trick.
// FIXME: remove all this bizarre padding horseshit once we start supporting
// nonmatching/shiftable builds.
#include "common.h"
#include "structs.h"

int gt2_main_race_switch_func0(gt2_race_entry* entry, gt2_race_part_type part_type, int index, int default_value) {

    int result = default_value;
    switch (part_type)
    {
        case 0:
            result = entry->entries0_1[index];
            break;
        case 1:
            result = entry->entries1_1[index];
            break;
        case 2:
            result = entry->entries2_1[index];
            break;
        case 3:
            result = entry->entries3_1[index];
            break;
        case 4:
            result = entry->entries4_1[index];
            break;
        case 5:
            result = entry->entries5_1[index];
            break;
        case GT2_PART_TYPE_GEAR:
            result = entry->entries6_1[index];
            break;
        case 7:
            result = entry->entries7_1[index];
            break;
        case 8:
            result = entry->entries8_1[index];
            break;
        case 9:
            result = entry->entries9_1[index];
            break;
        case 10:
            result = entry->entries10_1[index];
            break;
        case 11:
            result = entry->entries11_1[index];
            break;
        case 12:
            result = entry->entries12_1[index];
            break;
        case 13:
            result = entry->entries13_1[index];
            break;
        case 14:
            result = entry->entries14_1[index];
            break;
        case 15:
            result = entry->entries15_1[index];
            break;
        case 16:
            result = entry->entries16_1[index];
            break;
        case 17:
            result = entry->entries17_1[index];
            break;
        case 18:
            result = entry->entries18_1[index];
            break;
        case 19:
            result = entry->entries19_1[index];
            break;
        case 20:
            result = entry->entries20_1[index];
            break;
        case 21:
            result = entry->entries21_1[index];
            break;
        case 22:
            result = entry->entries22_1[index];
            #ifdef MATCHING
            asm("nop");
            #else
            break;
            #endif
        default:
            return result;
    }

    return result;
}

// HACK HACK HACK
#ifdef MATCHING
static const int padding = 0;
#endif
