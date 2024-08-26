// Thanks to nenkai for the solve!
// builds only with GCC 2.8.1
#include "common.h"
#include "structs.h"

extern char* D_8009118C[248]; // gt2_vol_used_dirs
extern int gt2_vol_buffer;   // gt2_vol_buffer
unsigned short gt2_vol_cached_dir_indices[256];   // gt2_vol_cached_dir_indices

void gt2_ovr0_vol_build_file_indices_cache(void) { // gt2_main_vol_build_file_indices_cache
    char** path_ptr = D_8009118C;
    unsigned short* indices_ptr = &gt2_vol_cached_dir_indices;
    gt2_vol_entry* entry;

    while (1)
    {
        if (*path_ptr == NULL)
            return;
        
        entry = gt2_ovr0_vol_search_vol_dir(*path_ptr, NULL); // gt2_main_vol_search_vol_dir
        *indices_ptr = 0xFFFF;
        
        if (entry) 
        {
            if ((GTFS_FILEINFO_FLAG_DIRECTORY(entry->entry_flags))) 
            {
                gt2_vol_entry* entries = (gt2_vol_entry*)&gt2_vol_buffer;
                entry = &entries[entry->next_dir_or_file_index] + 1;
            }
            
            *indices_ptr = entry->next_dir_or_file_index;
        }
        
        path_ptr++;
        indices_ptr++;
    }
}
