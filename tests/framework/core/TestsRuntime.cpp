#include "TestsRuntime.hpp"
#include "Emoji.hpp"

#include <platform/Platform.hpp>
#include <utility/ProgramOptions.hpp>
#include <types/Timer.hpp>
#include <utility/Assert.hpp>


namespace Ruby::Testify {
    void TestsRuntime::Register(String label, ITest* test) {
        m_tests.emplace_back(
            std::make_pair(
                std::move(label), test));
    }

    void TestsRuntime::RunTest(const String& label, ITest* test) {
        test->Run();

        writeInConsoleF("[ PASSED ]: {}\n", label.c_str());
    }

    i32 TestsRuntime::RunAllTests(const ProgramOptions& opts) const {
        return RunAllRegisteredTests(); // Temporary
        // RunFromCommandLine(std::move(args));
    }


    i32 TestsRuntime::TestAll(const StorageType& testsStorage) const {
        u64 countOfSuccessfulTests = 0;
        Ruby::Time::StopWatch stopWatch{};

        for (const auto& [label, test] : testsStorage) {
            try {
                RunTest(label, test);
                ++countOfSuccessfulTests;
            }
            catch(const std::exception& err) {
                writeInConsoleF("[ FAILED ]: Failed: {}\n", err.what());
            }
        }
        
        writeInConsoleF("\n\n------Tests Results------\n");
        writeInConsoleF("-- Tests passed: {}/{}\n", countOfSuccessfulTests, m_tests.size());
        writeInConsoleF("-- Elapsed time: {}\n", stopWatch.GetElapsed().count());

        return (countOfSuccessfulTests != m_tests.size());
    }


    i32 TestsRuntime::RunAllRegisteredTests() const {
        if (m_tests.empty()) {
            Platform::writeInConsole("Nothing to test\n");
            return 0;
        }

        return TestAll(m_tests);
    }


    void TestsRuntime::RunFromCommandLine(ProgramOptions&& args) {

    }


    TestsRuntime::StorageType TestsRuntime::GetAllTestsCopy() const {
        return m_tests;
    }

    const TestsRuntime::StorageType& TestsRuntime::GetAllTestsRef() const {
        return m_tests;
    }
}