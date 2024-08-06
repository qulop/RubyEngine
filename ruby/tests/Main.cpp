#include <utility/CommandLineArgs.hpp>

#include "UnitTester.hpp"
#include "cases/TestCases.hpp"


int main(int argc, char** argv) {
    Ruby::CommandLineArgs args{ argc, argv };

    auto&& tester = Ruby::Tests::UnitTester::GetInstance();
    tester.Init();

    tester.AddTest("EnumReflector", Ruby::Tests::EnumTest::Test);
    tester.AddTest("Events", Ruby::Tests::EventsTest::Test);

    tester.TestAll();

    return 0;
}