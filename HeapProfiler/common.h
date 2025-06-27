#ifndef COMMON_H
#define COMMON_H

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include <tchar.h>
#include <psapi.h>

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

#define ADDRESS32 DWORD32
#define ADDRESS64 DWORD64

using namespace std;
#endif