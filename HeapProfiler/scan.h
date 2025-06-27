#ifndef SCAN_H
#define SCAN_H
#include "common.h"

struct MallocVersion {
  char* name;
  char* pattern;
  char* mask;
  void* detour;
  void** original;
  MallocVersion(char* name, char* pattern, char* mask, void* detour, void** original) : name(name), pattern(pattern), mask(mask), detour(detour), original(original) {

  }
};

class MallocFunc {
public:
	MallocVersion version;
	ADDRESS addr;
	
	MallocFunc(MallocVersion version, ADDRESS addr) : version(version), addr(addr) {};
};

vector<ADDRESS> FindPattern(ADDRESS base, ADDRESS size, char pattern[], char mask[] );
vector<MallocFunc> ScanRegion(MEMORY_BASIC_INFORMATION Mem);
#endif