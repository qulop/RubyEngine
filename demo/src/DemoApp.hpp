#include <RubyEngine.hpp>


class Demo final : public Ruby::RubyApp
{
public:
    Demo(Ruby::VideoAttr& va) :
        RubyApp(va)
    {}

    void Update(double deltaTime) override
    {
        // Write your code here
    }

    virtual ~Demo()
    {}
};
