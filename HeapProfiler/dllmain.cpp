
#include "common.h"

#include "memory.h"
#include "scan.h"
#include "hooks.h"

#include "gui.h"
#include <thread>

void GUIThread() {
    initGUI();
}

void mainThread() {
    MH_Initialize();

    MODULEINFO heapprof_info = GetModuleInfo(L"HeapProfiler.dll");

    vector<MallocFunc> mallocs_found;

    vector<MEMORY_BASIC_INFORMATION> regions = GetMemoryRegions();
    for (int i = 0; i < regions.size(); i++) {
        MEMORY_BASIC_INFORMATION Mem = regions[i];

        // don't scan ourselves
        if ((heapprof_info.lpBaseOfDll <= Mem.BaseAddress) && ((ADDRESS)Mem.BaseAddress < (ADDRESS)heapprof_info.lpBaseOfDll + (ADDRESS)heapprof_info.SizeOfImage)) {
            continue;
        }

        // we are looking for a function, therefore it should be in an executable memory region
        if (isExecutable(Mem.Protect)) {
            vector<MallocFunc> found = ScanRegion(Mem);
            mallocs_found.insert(mallocs_found.end(), found.begin(), found.end());
        }
        //GUI_setScanProgress((float)(i+1) / regions.size());
    }

    for (auto m : mallocs_found) {
        createHook(m);    
        //GUI_addMallocFunc(to_hex(m.addr) + ": " + m.version.name + " in " + GetModuleNameAt(m.addr));
    }

    
}

BOOL APIENTRY DllMain(HINSTANCE hInst     /* Library instance handle. */,
    DWORD reason        /* Reason this function is being called. */,
    LPVOID reserved     /* Not used. */)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:        
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)GUIThread, 0, 0, 0);
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)mainThread, 0, 0, 0);
        break;

    case DLL_PROCESS_DETACH:

        break;

    case DLL_THREAD_ATTACH:

        break;

    case DLL_THREAD_DETACH:


        break;
    }

    return TRUE;
}

