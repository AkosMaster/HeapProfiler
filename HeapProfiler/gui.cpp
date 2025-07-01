#include "gui.h"
#include <sstream>
#include <iomanip>
#include "memory.h"

#include "tracking.h"

#include "hello_imgui/hello_imgui.h"
#include <set>

std::string to_hex(ADDRESS i)
{
    std::stringstream stream;
    stream << "0x"
        << std::setfill('0') << std::setw(sizeof(ADDRESS) * 2)
        << std::hex << i;
    return stream.str();
}

float scanProgress = 0;
void GUI_setScanProgress(float p) {
    scanProgress = p;
}

unordered_map<ADDRESS, AllocationInfo> allocations_copy;

void TreeDraw(ADDRESS addr, set<ADDRESS>* visited) {
    
    if (visited->find(addr) != visited->end()) {
        ImGui::Text(to_hex(addr).c_str());
        return;
    }
    visited->insert(addr);

    if (ImGui::TreeNode(to_hex(addr).c_str())) {
        for (ADDRESS c_addr : allocations_copy[addr].children) {
            TreeDraw(c_addr, visited);
        }

        ImGui::TreePop();
    }
}

void initGUI() {
    
    HelloImGui::Run(
        [] { 
            ImGui::BeginTabBar("Settings#left_tabs_bar");

            if (ImGui::BeginTabItem("Hooks")) {
                ImGui::Text("Function scan progress:");
                ImGui::ProgressBar(scanProgress);

                ImGui::BeginListBox("Hooks");
                {
                    ImGui::Selectable("TODO1");
                    ImGui::Selectable("TODO2");
                    ImGui::Selectable("TODO3");

                    ImGui::EndListBox();
                }

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Allocations")) {

                if (ImGui::Button("Refresh")) {
                    refreshChildren();
                    allocations_copy = getAllocations();
                }

                // draw tree of allocations
                for (auto it = allocations_copy.begin(); it != allocations_copy.end(); it++)
                {
                    if (!it->second.pointed_to) {
                        set<ADDRESS> visited;
                        TreeDraw(it->first, &visited);
                    }
                }

                ImGui::EndTabItem();
            }

            

            ImGui::EndTabBar();
        }, // Gui code
        "HeapProfiler", true);                     // Window title + Window size auto
    
}