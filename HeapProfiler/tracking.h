#ifndef TRACKING_H
#define TRACKING_H
#include "common.h"
#include <map>

struct AllocationInfo {
	DWORD32 handlerID;
	ADDRESS addr;
	size_t size;
};

extern map<ADDRESS, AllocationInfo> allocations;

vector<AllocationInfo> allocationList();

void cb_malloc(DWORD32 hId, ADDRESS addr, size_t size);
void cb_free(DWORD32 hId, ADDRESS addr);

#endif