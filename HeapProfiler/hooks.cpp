
#include "hooks.h"

#include <iostream>
#include <stacktrace>

void* o_malloc_msvcrtx86_0 = 0;
ADDRESS32 hk_malloc_msvcrtx86_0(size_t size) {
	cout << "hook!" << endl;
	system("pause");
	return 0;
}

void* o_malloc_msvcrtx64_0 = 0;
ADDRESS64 hk_malloc_msvcrtx64_0(size_t size) {
	cout << "hook! original: " << hex << o_malloc_msvcrtx64_0 << endl;
	
	cout << "size: " << size << " | ret: ";
	ADDRESS64 v = ((ADDRESS64(*)(size_t))o_malloc_msvcrtx64_0)(size);
	cout << hex << v << endl;
	return v;
}

void createHook(MallocFunc func) {
	if (MH_CreateHook((void*)func.addr, (void*)func.version.detour, func.version.original) != MH_OK)
	{
		cout << "HPROF> error: createHook error" << endl;
	}
	if (MH_EnableHook((void*)func.addr) != MH_OK)
	{
		cout << "HPROF> error: enableHook error" << endl;
	}
}