#include "gui.h"
#include <sstream>
#include <iomanip>
#include "memory.h"

#include "tracking.h"

#include "hello_imgui/hello_imgui.h"

std::string to_hex(ADDRESS i)
{
    std::stringstream stream;
    stream << "0x"
        << std::setfill('0') << std::setw(sizeof(ADDRESS) * 2)
        << std::hex << i;
    return stream.str();
}

void initGUI() {
    
    cout << "running hello-imgui" << endl;
    HelloImGui::Run(
        [] { ImGui::Text("Hello, world!"); }, // Gui code
        "Hello!", true);                     // Window title + Window size auto
    
}