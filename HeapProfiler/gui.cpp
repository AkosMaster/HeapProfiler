#include "gui.h"

void initGUI() {
    using namespace ftxui;

    vector<string> modules = GetModuleNames();
    
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