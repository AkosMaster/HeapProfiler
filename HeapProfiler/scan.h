#ifndef SCAN_H
#define SCAN_H
#include "common.h"

struct MallocVersion {
  char* name;
  char* pattern;
  char* mask;
  
  string dll;
  MallocVersion(char* name, char* pattern, char* mask, string dll) : name(name), pattern(pattern), mask(mask), dll(dll) {

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