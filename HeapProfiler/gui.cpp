#include "gui.h"
#include <sstream>
#include <iomanip>
#include "memory.h"
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include "tracking.h"

using namespace ftxui;

ScreenInteractive* screen;

ButtonOption ButtonStyle() {
    auto option = ButtonOption::Animated();
    option.transform = [](const EntryState& s) {
        auto element = text(s.label);
        if (s.focused) {
            element |= bold;
        }
        return element | center | borderEmpty | flex;
        };
    return option;
}

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

vector<string> allocationTitles = {};
int allocation_selected = 0;
void GUI_refreshAllocList() {
    allocationTitles.clear();
    auto infos = allocationList();
    for (auto info : infos) {
        allocationTitles.push_back(to_hex(info.addr) + ": " + to_hex(info.size));
    }
    screen->PostEvent(Event::Custom);
}

void initGUI() {

    std::vector<std::string> tab_values{
      "Hooks",
      "Allocations",
      "Options",
    };

    // TAB_HOOKS

    auto hooks_menu = Menu(&mallocFuncs, &malloc_selected);
    auto tab_hooks = Renderer(hooks_menu, [&] {
        return vbox({
            text("Scan progress:"),
            gauge(scanProgress),

            window(text("Hooks"), {
                hooks_menu->Render() | vscroll_indicator | frame |
           size(HEIGHT, LESS_THAN, 10) | border
            })
        });
    });
    // TAB_ALLOCS
    auto allocs_btn = Button("Refresh", [] { GUI_refreshAllocList(); });
    auto allocs_menu = Menu(&allocationTitles, &allocation_selected);

    auto allocs_menu_renderer = Renderer(allocs_menu, [&] {
        return vbox({
            window(text("Allocations"), {
                allocs_menu->Render() | vscroll_indicator | frame |
           size(HEIGHT, LESS_THAN, 10) | border
            }),
        });
    });
    auto tab_allocs = Container::Vertical({
        allocs_btn, allocs_menu_renderer    
    });

    // MAIN WINDOW

    int tab_selected = 0;
    auto tab_toggle = Toggle(&tab_values, &tab_selected);
    
    auto tab_container = Container::Tab(
        {
            tab_hooks,
            tab_allocs,
            Renderer([&] {return text("TODO"); }),
        },
        &tab_selected);

    auto main_container = Container::Vertical({
        tab_toggle,
        tab_container,
    });

    auto GUIRenderer = Renderer(main_container, [&] {
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