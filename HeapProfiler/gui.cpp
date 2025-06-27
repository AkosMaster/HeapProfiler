#include "gui.h"
#include <sstream>
#include <iomanip>

std::string to_hex(ADDRESS i)
{
    std::stringstream stream;
    stream << "0x"
        << std::setfill('0') << std::setw(sizeof(ADDRESS) * 2)
        << std::hex << i;
    return stream.str();
}

void initGUI(vector<MallocFunc>& mallocs) {
    using namespace ftxui;

    vector<string> modules;
    for (auto m : mallocs) {
        modules.push_back(to_hex(m.addr) + ": " + m.version.name + " in " + GetModuleNameAt(m.addr));
    }
    
    int selected = 0;
    
    ftxui::Component menu = ftxui::Menu(&modules, &selected);

    Element document = hbox({
      text("left") | border,
      text("middle") | border | flex,
      text("right") | border,
        });
    
    auto screen = ScreenInteractive::FitComponent();
    
    auto renderer = Renderer(menu, [&] { return menu->Render() | ftxui::vscroll_indicator | frame; });
    //auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
    //Render(screen, document);
    //screen.Print();
    screen.Loop(renderer);
}