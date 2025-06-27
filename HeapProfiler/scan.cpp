
#include "scan.h"
#include "memory.h"
#include "hooks.h"

std::vector<MallocVersion> malloc_versions = {
  MallocVersion((char*)"msvcrt_x86_0", (char*)"\x8b\xff\x55\x8b\xec\x83\x3d\x00\x00\x00\x00\x00\x75\x00\xe8", (char*)"xxxxxxx?????x?x", (void*)&hk_malloc_msvcrtx86_0, &o_malloc_msvcrtx86_0),
  MallocVersion((char*)"msvcrt_x64_0", (char*)"\x48\x89\x5c\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xec\x00\x48\x83\x3d", (char*)"xxxx?xxxx?xxxx?xxx", (void*)&hk_malloc_msvcrtx64_0, &o_malloc_msvcrtx64_0)
};

vector<ADDRESS> FindPattern(ADDRESS base, ADDRESS size, char pattern[], char mask[] )
{
	vector<ADDRESS> found;
    for( ADDRESS retAddress = base; retAddress < (base + size - strlen(mask)); retAddress++ )
    {
        if( *(BYTE*)retAddress == (pattern[0]&0xff) || mask[0] == '?' )
        {
            ADDRESS startSearch = retAddress;
            for( int i = 0; mask[i] != '\0' ; i++, startSearch++ )
            {
                if( (pattern[i]&0xff) != *(BYTE*)startSearch && mask[i] != '?')
                    break;
                
                if( ((pattern[i]&0xff) == *(BYTE*)startSearch || mask[i] == '?') && mask[i+1] == '\0' )
                    found.push_back(retAddress);
            }        
        }
    }
 
    return found;
}

vector<MallocFunc> ScanRegion(MEMORY_BASIC_INFORMATION Mem) {
    vector<MallocFunc> found;
    DWORD oldprotect;
    if (VirtualProtect(Mem.BaseAddress, Mem.RegionSize, PAGE_EXECUTE_READWRITE, &oldprotect) == 0) {
      //cout << "error: " << hex << GetLastErrorAsString() << "\n";
    } else {
        for (int i = 0; i < malloc_versions.size(); i++) {
            vector<ADDRESS> addrs = FindPattern((ADDRESS)Mem.BaseAddress, (ADDRESS)Mem.RegionSize, malloc_versions[i].pattern, malloc_versions[i].mask);
            for (int j = 0; j < addrs.size(); j++) {
                cout << malloc_versions[i].name << " at " << hex << addrs[j] << " in "; PrintModName(GetModuleAt(addrs[j])); cout << "\n";
                  found.push_back(MallocFunc(malloc_versions[i], addrs[j]));
            }
        }

        // restore protecion
        DWORD oldprotect2;
        VirtualProtect(Mem.BaseAddress, Mem.RegionSize, oldprotect, &oldprotect2);
    }
    return found;
}