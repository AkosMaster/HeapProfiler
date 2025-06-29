
#define WIN32_LEAN_AND_MEAN

//#include <windows.h>
//#include <iostream>
#include <stdint.h>
using namespace std;
#define DLL1_API __declspec(dllexport)

#define DWORD32 uint32_t
#define DWORD64 uint64_t

#if INTPTR_MAX == INT64_MAX
#define ADDRESS DWORD64
#pragma message ( "64-bit compilation detected!" )
#define VERSION 64
#elif INTPTR_MAX == INT32_MAX
#define ADDRESS DWORD32
#pragma message ( "32-bit compilation detected!" )
#define VERSION 32
#else
#error Unknown pointer size!
#endif

#define ADDRESS64 DWORD64
#define ADDRESS32 DWORD32

DWORD32 handlerID = -1;
ADDRESS ofunc;

extern "C" DLL1_API void InitHandler(DWORD32 _handlerID, ADDRESS _ofunc) {
    handlerID = _handlerID;
    ofunc = _ofunc;
}

/* 
	default 'malloc' handler for x64/x86.
*/
#ifdef HOOK_TYPE_MALLOC
extern "C" ADDRESS DLL1_API hook(size_t size) {
	//cout << handlerID << ": " << "size: " << size << " | ret: ";

	ADDRESS v = ((ADDRESS(*)(size_t))ofunc)(size);
	//cout << hex << v << endl;
	return v;
}
#endif

/*
	default 'free' handler for x64/x86.
*/
#ifdef HOOK_TYPE_FREE
extern "C" void DLL1_API hook(ADDRESS addr) {
	//cout << "free hooked" << endl;
	((void(*)(ADDRESS))ofunc)(addr);
}
#endif