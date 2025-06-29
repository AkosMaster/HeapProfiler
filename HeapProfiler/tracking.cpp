#include "tracking.h"

map<ADDRESS, AllocationInfo> allocations;

void cb_malloc(DWORD32 hId, ADDRESS addr, size_t size) {
	
	allocations[addr] = AllocationInfo{ hId, addr, size };
}

void cb_free(DWORD32 hId, ADDRESS addr) {

}

vector<AllocationInfo> allocationList() {
	vector<AllocationInfo> vals;
	
	for (auto it = allocations.begin(); it != allocations.end(); it++)
	{
		vals.push_back(it->second);
	}
	return vals;
}