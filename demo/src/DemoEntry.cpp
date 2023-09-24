#include "DemoApp.hpp"
#include <memory>


int main()
{
    Ruby::WindowAttributes wa;
    wa.title = "Ruby Demo";
    wa.width = 300;
    wa.height = 300;    

    std::unique_ptr<Demo> demoVn{ new Demo{ wa } };

    if (demoVn->Run() != 0)
        return 1;    
    return 0;
}