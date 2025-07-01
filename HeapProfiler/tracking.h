#ifndef TRACKING_H
#define TRACKING_H
#include "common.h"
#include <unordered_map>

struct AllocationInfo {
	DWORD32 handlerID;
	ADDRESS addr;
	size_t size;

	vector<ADDRESS> children;
	bool pointed_to = false;
};

unordered_map<ADDRESS, AllocationInfo> getAllocations();
void refreshChildren();

void cb_malloc(DWORD32 hId, ADDRESS addr, size_t size);
void cb_free(DWORD32 hId, ADDRESS addr);

#endif