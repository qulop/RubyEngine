#include "TestsRuntime.hpp"

#include <types/Logger.hpp>
#include <core/Timer.hpp>


namespace Ruby::Testify {
    void TestsRuntime::AddTest(RubyString label, ITest* test) { 
        m_tests.emplace_back(
            std::make_pair(
                std::move(label), test));
    }

    void TestsRuntime::RunTest(RubyString label, ITest* test) {
        static u64 testNumber = 1;

        fprintf_s(stdout, "[%d] Test: \"%s\"...", label.c_str());


    }

    void TestsRuntime::TestAll(const StorageType& testsStorage) {
        Ruby::Time::StopWatch stopWatch{};

        u64 countOfSuccessfulTests = 0;
        for (const auto& t : testsStorage) {
            try {
                RunTest(t.first, t.second);
                ++countOfSuccessfulTests;
            }
            catch(...) {

            }
        }
        
        fprintf_s(stdout, "\n\n------Tests Results------\n");
        fprintf_s(stdout, "-- Tests passed: %d/%d\n", countOfSuccessfulTests, m_tests.size());
        // fprintf_s(stdout, "-- Elapsed time: %s\n", Ruby::Time::prettifyTime(
        //     stopWatch.Elapsed().count()));
    }


    void TestsRuntime::RunAllRegistredTests() {
        if (!m_tests.size()) {
            fprintf_s(stdout, "-- TestsRuntime::RunAllRegistredTests() : Nothing to test --");
            return;
        }

        TestAll(m_tests);
    }

    TestsRuntime::StorageType TestsRuntime::GetAllTestsCopy() const {
        return m_tests;
    }

    const TestsRuntime::StorageType& TestsRuntime::GetAllTestsRef() const {
        return m_tests;
    }
}