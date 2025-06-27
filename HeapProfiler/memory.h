#ifndef MEMORY_H
#define MEMORY_H
#include "common.h"

string GetModuleNameAt(ADDRESS address);
vector<string> GetModuleNames();
void PrintRegion(MEMORY_BASIC_INFORMATION Mem);
vector<MEMORY_BASIC_INFORMATION> GetMemoryRegions();
MODULEINFO GetModuleInfo( LPCWSTR szModule );
//HMODULE GetModuleAt(ADDRESS addr);

bool isExecutable(DWORD protection);


#endif