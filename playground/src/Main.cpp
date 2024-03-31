#include "PlaygroundApp.hpp"


int main()
{
    Ruby::VideoStruct va { "Playground Demo", true };
    Ruby::Font font { "C:\\Windows\\Fonts\\arial.ttf", 20 };

    auto playground = Ruby::RubyApp::CreateApp<Playground>(va, font);

    if (!playground->Mainloop())
        return 1;
    return 0;
}