
#include "memory.h"

vector<string> GetModuleNames()
{
    DWORD processID = GetCurrentProcessId();
    vector<string> names;

    HMODULE hMods[1024];
    HANDLE hProcess;
    DWORD cbNeeded;
    unsigned int i;

    // Print the process identifier.

    // Get a handle to the process.

    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
        PROCESS_VM_READ,
        FALSE, processID);
    if (NULL == hProcess)
        return names;

    // Get a list of all the modules in this process.
    if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
    {
        for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
        {
            TCHAR szModName[MAX_PATH];

            // Get the full path to the module's file.

            if (GetModuleFileNameEx(hProcess, hMods[i], szModName,
                sizeof(szModName) / sizeof(TCHAR)))
            {
                // Print the module name and handle value.

                //_tprintf(TEXT("\t%s (0x%08X)\n"), szModName, hMods[i]);
                wstring wstr = wstring(szModName);
                names.push_back(string(wstr.begin(), wstr.end()));
            }
        }
    }
    CloseHandle(hProcess);
    return names;
}

void PrintRegion(MEMORY_BASIC_INFORMATION Mem) {
  std::cout << std::hex << 
  Mem.BaseAddress 
  << " - " << (LPVOID)(Mem.RegionSize + (ADDRESS)Mem.BaseAddress) 
  << " - size:(" << std::dec << Mem.RegionSize 
  << ")\n";
}

vector<MEMORY_BASIC_INFORMATION> GetMemoryRegions() {
   /*HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                            PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION,
                            FALSE, GetCurrentProcessId() );*/
   // memory regions
   ADDRESS addr(0);
   vector<MEMORY_BASIC_INFORMATION> regions;

   MEMORY_BASIC_INFORMATION Mem;

   // Start querying
   while (VirtualQuery((void*)addr, &Mem, sizeof(MEMORY_BASIC_INFORMATION)))
   {
        regions.push_back(Mem);
        addr += Mem.RegionSize;
   }
   return regions;
}

MODULEINFO GetModuleInfo( LPCWSTR szModule )
{
    MODULEINFO modinfo = {0};
    HMODULE hModule = GetModuleHandle(szModule);
    if(hModule == 0) 
        return modinfo;
    GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
    return modinfo;
}

HMODULE GetModuleAt(ADDRESS addr) {
    MEMORY_BASIC_INFORMATION mbi;
    if (VirtualQuery((void*)addr, &mbi, sizeof(mbi)))
    {
        return (HMODULE)mbi.AllocationBase;
    }
}

void PrintModName(HMODULE mod) {
    TCHAR szModName[MAX_PATH];
    if (GetModuleFileName(mod, szModName,
        sizeof(szModName) / sizeof(TCHAR)))
    {
        _tprintf(TEXT("%s"), szModName);
    }
    else {
        cout << "error";
    }
}

// is there a better way? :)
bool isExecutable(DWORD protection) {
    return protection == PAGE_EXECUTE || protection == PAGE_EXECUTE_READ || protection == PAGE_EXECUTE_READWRITE || PAGE_EXECUTE_WRITECOPY;
}