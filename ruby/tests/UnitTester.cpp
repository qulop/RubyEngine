#include "UnitTester.hpp"


namespace Ruby::Tests
{
    void UnitTester::Init(void)
    { Logger::GetInstance().Init(); }


    void UnitTester::AddTest(const RubyString& label, UnitTester::CallbackType&& callback)
    { m_tests[label] = std::move(callback); }


    bool UnitTester::RunTest(const RubyString& label, UnitTester::CallbackType&& callback)
    {
        RUBY_INFO("Running test for target {}...", label);
        bool isSuccess = callback();
        if (!isSuccess)
            RUBY_ERROR("    Test Failed.");
        else
            RUBY_INFO("     Test Passed.");

        return isSuccess;
    }


    bool UnitTester::TestAll(void)
    {
        size_t successTests = 0;

        for (auto&& [label, callback] : m_tests)
        {
            if (RunTest(label, std::move(callback)))
                ++successTests;
        }

        RUBY_INFO("Test passed: {}/{}", successTests, m_tests.size());
        return successTests == m_tests.size();
    }
}