// Thanks to nenkai for the final solve!
// Only builds on 2.8.1
#include "common.h"

// Pre-generated CRC32 Table from Polynomial 0xEDB88320:
extern u32 gt2_CRC32_constant_table[];

u32 gt2_save_crc32(const u8* cstr, size_t len) {
    u32 crc = 0xFFFFFFFF;
    u8* ptr = cstr;
    u8* end = &ptr[len];
    u32* tbl = gt2_CRC32_constant_table;

    if (len != 0) {
        do {
            crc = tbl[((crc ^ *ptr++) & 0xFF)] ^ (crc >> 8);
        } while (ptr != end);
    }
    return ~crc;
}
