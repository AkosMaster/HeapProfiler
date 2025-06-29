#include "gui.h"
#include <sstream>
#include <iomanip>
#include "memory.h"
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

using namespace ftxui;

ScreenInteractive* screen;

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
    screen->PostEvent(Event::Custom);
}
vector<string> mallocFuncs;
int malloc_selected = 0;
void GUI_addMallocFunc(string desc) {
    screen->Post([desc]() {
        mallocFuncs.push_back(desc);
        screen->PostEvent(Event::Custom);
    });
}

ftxui::Component TAB_hooks() {
    auto container = Container::Horizontal({
        Menu(&mallocFuncs, &malloc_selected),
    });
    return Renderer(container, [&] { 
        return vbox({
            text("Scan progress:"),
            gauge(scanProgress),
            
            window(text("Hooks"), {
                container->Render()
            })
        });
    });
    
}

void initGUI() {

    std::vector<std::string> tab_values{
      "Hooks",
      "Allocations",
      "Options",
    };
    int tab_selected = 0;
    auto tab_toggle = Toggle(&tab_values, &tab_selected);
    
    auto tab_container = Container::Tab(
        {
            TAB_hooks(),
            Renderer([&] {return text("TODO"); }),
            Renderer([&] {return text("TODO"); }),
        },
        &tab_selected);

    auto container = Container::Vertical({
        tab_toggle,
        tab_container,
    });

    auto GUIRenderer = Renderer(container, [&] {
        return vbox({
                   tab_toggle->Render(),
                   separator(),
                   tab_container->Render(),
            }) |
            border;
        });
    ScreenInteractive _screen = ScreenInteractive::TerminalOutput();
    screen = &_screen;
    _screen.Loop(GUIRenderer);
}