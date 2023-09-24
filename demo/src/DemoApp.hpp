#include <RubyVn.hpp>

#if defined(DEMO_INHERIT)
    #define FINAL
#else
    #define FINAL final
#endif


class Demo FINAL : public Ruby::RubyApp
{
public:
    Demo(Ruby::WindowAttrubutes& wa) :
        RubyApp(wa)
    {}

    ~Demo()
    {}
};