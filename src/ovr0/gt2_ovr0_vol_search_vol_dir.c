// thanks to Nenkai for solving this one
#include "common.h"

typedef struct {
    int date_time;
    unsigned short next_dir_or_file_index;
    unsigned char  entry_flags; // 0x00 = file, 0x01 = dir, 0x80 = end of dir
    char name[25];
} gt2_vol_entry;

extern gt2_vol_entry D_800A97D0[17920]; // All vol files - 0x8C000 / 0x20?
    
gt2_vol_entry* gt2_ovr0_vol_search_vol_dir(char* path, gt2_vol_entry* vol_entry) { // gt2_main_vol_loader

    char buffer[0x100];
    
    gt2_vol_entry* root = D_800A97D0;
    char next = path[1];
   
    if (*(signed char*)path == '/')
    {
        path++;
        if (!next)
            return root;

        vol_entry = 0;
    }

    if (vol_entry == NULL)
        vol_entry = root;

    while (1)
    {
        gt2_vol_entry* current_entry;
        int part_length;
        
        char* end = gt2_ovr0_strchr(path, '/'); // gt2_ovr0_strchr
        if (!end)
            break;
        
        part_length = end - path;
        gt2_main_strcpy(buffer, path, part_length); // gt2_main_strcpy
        buffer[part_length] = '\0';
        current_entry = gt2_ovr0_vol_search_vol_dir(buffer, vol_entry);
        path = end + 1;
        vol_entry = current_entry;
        if (!vol_entry)
            return NULL;

        vol_entry = &D_800A97D0[current_entry->next_dir_or_file_index];
    }

    while (1)
    {
        if (gt2_main_strcmp(vol_entry->name, path) == 0) // gt2_main_strcmp
            return vol_entry;

        // Is not end of dir?
        if ((vol_entry->entry_flags & 0x80) == 0)
        {
            vol_entry++;
            continue;
        }
        else
            return NULL;
    }
    
    return NULL;
}