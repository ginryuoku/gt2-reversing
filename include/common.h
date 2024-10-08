#ifndef COMMON_H
#define COMMON_H

#include "asm.h"

// boilerplate C/C++isms
#define NULL 0

// GTFS defines
#define GTFS_SECTOR_OFFSET(packed_value) (packed_value >> 11)
#define GTFS_FILEINFO_FLAG_DIRECTORY(file_info_flags) (file_info_flags & 1)

// project-specific defines
// this determines if the build uses disgusting alignment hacks or not.
#define MATCHING 

typedef signed int s32;
typedef signed short s16;
typedef signed char s8;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef unsigned int size_t;

#endif /* COMMON_H */
