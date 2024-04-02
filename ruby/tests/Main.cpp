#include <utility/RubyUtility.hpp>

#include "instance/UnitTester.hpp"


int main(int argc, char** argv)
{
    auto&& tester = Ruby::Tests::UnitTester::GetInstance();
    tester.Init();

    tester.AddTest("Simple test", [] {
        if ((2 + 2) == 4)
            return true;
        return false;    
    });

    tester.RunAll();

    return 0;
}