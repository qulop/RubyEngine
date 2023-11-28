#include "DemoApp.hpp"
#include <memory>


int main()
{
    Ruby::VideoAttr va { "Demo", 300, 300 };
    va.isResizable = false;

    std::unique_ptr<Demo> demoVn = std::make_unique<Demo>(va);
    auto errCode = demoVn->Mainloop();

    if (!errCode)
    {
        return 1;
    }    
    return 0;
}