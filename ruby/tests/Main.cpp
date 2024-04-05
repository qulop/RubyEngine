#include <utility/RubyUtility.hpp>

#include "instance/UnitTester.hpp"
#include "cases/TestCases.hpp"


int main(int argc, char** argv)
{
    auto&& tester = Ruby::Tests::UnitTester::GetInstance();
    tester.Init();

    tester.AddTest("EnumReflector", Ruby::Tests::EnumTest::Test);

    if (!tester.TestAll())
        RUBY_ERROR("Tests failed.");

    return 0;
}