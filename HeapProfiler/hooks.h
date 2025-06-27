#ifndef HOOKS_H
#define HOOKS_H
#include "common.h"
#include "scan.h"
#include "MinHook.h"

// not needed, we just do it from build32.cmd
#if VERSION == 64
	#pragma comment(lib, "libMinHook.x64.lib")
#elif VERSION == 32
	#pragma comment(lib, "libMinHook.x86.lib")
#else
	#error No hooking library found for this build version!
#endif

#include <intrin.h>

#pragma intrinsic(_ReturnAddress)

void createHook(MallocFunc func);

// malloc hook versions:
extern void* o_malloc_msvcrtx86_0;
ADDRESS32 hk_malloc_msvcrtx86_0(size_t size);

extern void* o_malloc_msvcrtx64_0;
ADDRESS64 hk_malloc_msvcrtx64_0(size_t size);

#endif