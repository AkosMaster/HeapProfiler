#include "tracking.h"
#include <mutex>
#include <unordered_map>
#include <set>

unordered_map<ADDRESS, AllocationInfo> allocations;
std::mutex allocations_mutex;

void cb_malloc(DWORD32 hId, ADDRESS addr, size_t size) {
	unique_lock<mutex>(allocations_mutex);
	allocations[addr] = AllocationInfo{ hId, addr, size };
}

void cb_free(DWORD32 hId, ADDRESS addr) {
	unique_lock<mutex>(allocations_mutex);
	// TODO
}

vector<AllocationInfo> allocationList() {
	unique_lock<mutex>(allocations_mutex);

	vector<AllocationInfo> vals;
	
	for (auto it = allocations.begin(); it != allocations.end(); it++)
	{
		vals.push_back(it->second);
	}
	return vals;
}

void refreshChildren() {
	unique_lock<mutex>(allocations_mutex);

	typedef void (*SignalHandlerPointer)(int);

	for (auto it = allocations.begin(); it != allocations.end(); it++)
	{
		ADDRESS addr = it->first;
		size_t size = it->second.size;

		allocations[addr].children.clear();
		// loop through memory of this allocation
		try {
			set<ADDRESS> found_children_addrs;
			for (ADDRESS curr_addr = addr; curr_addr < addr + size; curr_addr++) {
				
				ADDRESS memval = *(ADDRESS*)curr_addr;

				// pointer to another allocation detected!
				if (allocations.find(memval) != allocations.end() && found_children_addrs.find(memval) == found_children_addrs.end()) {
					
					allocations[memval].pointed_to = true;
					allocations[addr].children.push_back(memval);
					found_children_addrs.insert(memval);
				}
			}
		}
		catch (...) {
			// shit happens
		}
	}
}

unordered_map<ADDRESS, AllocationInfo> getAllocations() {
	return allocations;
}



