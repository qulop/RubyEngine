#include <utility/RubyUtility.hpp>

#include "UnitTester.hpp"
#include "cases/TestCases.hpp"


int main(int argc, char** argv)
{
    auto&& tester = Ruby::Tests::UnitTester::GetInstance();
    tester.Init();

    tester.AddTest("EnumReflector", Ruby::Tests::EnumTest::Test);
    tester.TestAll();

    return 0;
}