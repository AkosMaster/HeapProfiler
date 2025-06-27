
#include "common.h"

#include "memory.h"
#include "scan.h"
#include "hooks.h"

#include "gui.h"

void mainThread() {
    
    MH_Initialize();

    

    
    MODULEINFO heapprof_info = GetModuleInfo(L"HeapProfiler.dll");
    //cout << "HPROF> base: " << heapprof_info.lpBaseOfDll << " | size: " << hex << heapprof_info.SizeOfImage << endl;

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
    }

    initGUI(mallocs_found);
}

BOOL APIENTRY DllMain(HINSTANCE hInst     /* Library instance handle. */,
    DWORD reason        /* Reason this function is being called. */,
    LPVOID reserved     /* Not used. */)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        //MessageBox (0, "From DLL\n", "Process Attach", MB_ICONINFORMATION);
        //MessageBoxA(0, "", "Heap Profiler injected!", MB_OK | MB_ICONINFORMATION);

        AllocConsole();
        freopen("CONIN$", "r", stdin);
        freopen("CONOUT$", "w", stdout);

        //cout << "< HPROF v0.1 >" << endl;

        // MinHook setup
        //cout << "HPROF> Initializing MinHook..." << endl;

        /*if (MH_Initialize() != MH_OK)
        {
            cout << "HPROF> error: MinHook setup failed!" << endl;
            //return FALSE;
        }*/
        //DisableThreadLibraryCalls(hInst);

        //cout << "HPROF> MinHook setup success" << endl;
        //cout << "HPROF> creating main thread" << endl;
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

