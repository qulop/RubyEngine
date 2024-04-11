#include "UnitTester.hpp"


namespace Ruby::Tests
{
    void UnitTester::Init()
    { Logger::GetInstance().Init(); }


    void UnitTester::AddTest(const RubyString& label, UnitTester::CallbackType&& callback)
    { m_tests[label] = std::move(callback); }


    bool UnitTester::RunTest(const RubyString& label, UnitTester::CallbackType&& callback)
    {
        bool isSuccess = callback();

        return isSuccess;
    }


    void UnitTester::TestAll()
    {
        size_t successTests = 0;

        for (auto&& [label, callback] : m_tests)
        {
            if (RunTest(label, std::move(callback)))
            {
                RUBY_INFO("Target {} : Test passed", label);
                ++successTests;
            }
            else
                RUBY_ERROR("Target {} : Test failed", label);
        }

        fprintf_s(stdout, "------------------\n");
        RUBY_INFO("Tests passed: {}/{}", successTests, m_tests.size());
    }
}