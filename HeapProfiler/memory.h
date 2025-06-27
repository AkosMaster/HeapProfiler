#ifndef MEMORY_H
#define MEMORY_H
#include "common.h"


vector<string> GetModuleNames();
void PrintRegion(MEMORY_BASIC_INFORMATION Mem);
void PrintModName(HMODULE mod);
vector<MEMORY_BASIC_INFORMATION> GetMemoryRegions();
MODULEINFO GetModuleInfo( LPCWSTR szModule );
HMODULE GetModuleAt(ADDRESS addr);

bool isExecutable(DWORD protection);


#endif