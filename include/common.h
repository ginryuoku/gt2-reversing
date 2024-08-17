#ifndef COMMON_H
#define COMMON_H

#include "asm.h"

#define NULL 0
#define GTFS_SECTOR_OFFSET(packed_value) (packed_value >> 11)
#define GTFS_FILEINFO_FLAG_DIRECTORY(file_info_flags) (file_info_flags & 1)

typedef signed int s32;

#endif /* COMMON_H */
