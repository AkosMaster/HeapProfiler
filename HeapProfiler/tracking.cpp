#include "tracking.h"

map<ADDRESS, AllocationInfo> allocations;

void cb_malloc(DWORD32 hId, ADDRESS addr, size_t size) {
	
	allocations[addr] = AllocationInfo{ hId, size };
}

void cb_free(DWORD32 hId, ADDRESS addr) {

}