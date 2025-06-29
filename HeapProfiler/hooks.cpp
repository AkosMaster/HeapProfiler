
#include "hooks.h"

#include "memory.h"
#include <string> 
#include <iostream>
#include <stacktrace>

static int nextHandlerID = 1;
class Handler {
	void* init;
	HMODULE handlerDLL;
	int id;
public:
	void Init(ADDRESS ofunc) {
		((void(*)(DWORD32, ADDRESS))init)(id, ofunc);
	}

	void* GetHook() {
		return GetProcAddress(handlerDLL, "hook");
	}

	Handler(string dllname) {
		id = nextHandlerID++;

		string dllPath = GetDLLFolder() + "\\" + dllname;
		string tempPath = GetDLLFolder() + "\\tmp\\handler_" + to_string(id) + ".dll";

		if (!CopyFileA(dllPath.c_str(), tempPath.c_str(), false)) {
			cout << "could not copy hookhandler from " << dllPath << endl;
		}

		handlerDLL = LoadLibraryA(tempPath.c_str());
		if (handlerDLL == 0) {
			cout << "could not load hookhandler from " << tempPath << endl;
			int x; cin >> x;
		}

		init = GetProcAddress(handlerDLL, "InitHandler");
	}
};

void createHook(MallocFunc func) {
	Handler* handler = new Handler(func.version.dll);
	void* ofunc;
	if (MH_CreateHook((void*)func.addr, (void*)handler->GetHook(), &ofunc) != MH_OK) //(void*)func.version.detour
	{
		cout << "HPROF> error: createHook error" << endl;
	}
	handler->Init((ADDRESS)ofunc);
	if (MH_EnableHook((void*)func.addr) != MH_OK)
	{
		cout << "HPROF> error: enableHook error" << endl;
	}
}