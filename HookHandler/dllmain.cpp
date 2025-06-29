
#define WIN32_LEAN_AND_MEAN

//#include <windows.h>
//#include <iostream>

using namespace std;
#define DLL1_API __declspec(dllexport)

#include <stdint.h>
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

ADDRESS cb_malloc;
ADDRESS cb_free;

extern "C" DLL1_API void InitHandler(DWORD32 _handlerID, ADDRESS _ofunc, ADDRESS _cb_malloc, ADDRESS _cb_free) {
    handlerID = _handlerID;
    ofunc = _ofunc;
	cb_malloc = _cb_malloc;
	cb_free = _cb_free;
}

/* 
	default 'malloc' handler for x64/x86.
*/
#ifdef HOOK_TYPE_MALLOC
extern "C" ADDRESS DLL1_API hook(size_t size) {
	ADDRESS addr = ((ADDRESS(*)(size_t))ofunc)(size);
	((void(*)(DWORD32, ADDRESS, size_t))cb_malloc)(handlerID, addr, size);
	return addr;
}
#endif

/*
	default 'free' handler for x64/x86.
*/
#ifdef HOOK_TYPE_FREE
extern "C" void DLL1_API hook(ADDRESS addr) {
	((void(*)(ADDRESS))ofunc)(addr);
	((void(*)(DWORD32, ADDRESS))cb_free)(handlerID, addr);
}
#endif