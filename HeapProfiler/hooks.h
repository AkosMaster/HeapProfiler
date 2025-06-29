#ifndef HOOKS_H
#define HOOKS_H
#include "common.h"
#include "MinHook.h"
#include "scan.h"

// not needed, we just do it from build32.cmd
#if VERSION == 64
	#pragma comment(lib, "libMinHook.x64.lib")
#elif VERSION == 32
	#pragma comment(lib, "libMinHook.x86.lib")
#else
	#error No hooking library found for this build version!
#endif

#include <intrin.h>

void createHook(MallocFunc func);

#endif