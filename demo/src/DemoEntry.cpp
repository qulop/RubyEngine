#include "DemoApp.hpp"
#include <memory>

int main()
{
    Ruby::WindowAttrubutes wa;
    wa.title = "Raven Demo";
    
    std::shared_ptr<Demo> demoVn{ new Demo{ wa } };

    auto err = demoVn->Run();
    if (err != 0)
        return 1;
    std::cout << "here\n";


    return 0;
}