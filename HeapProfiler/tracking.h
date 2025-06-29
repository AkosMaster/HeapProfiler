#ifndef TRACKING_H
#define TRACKING_H
#include "common.h"
#include <map>

struct AllocationInfo {
	DWORD32 handlerID;
	size_t size;
};

extern map<ADDRESS, AllocationInfo> allocations;

void cb_malloc(DWORD32 hId, ADDRESS addr, size_t size);
void cb_free(DWORD32 hId, ADDRESS addr);

#endif