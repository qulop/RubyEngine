#include "UnitTester.hpp"


namespace Ruby::Tests
{
    void UnitTester::Init(void)
    { Logger::GetInstance().Init(); }


    void UnitTester::AddTest(const RubyString& label, UnitTester::CallbackType&& callback)
    { m_tests[label] = std::move(callback); }


    bool UnitTester::RunTest(const RubyString& label, UnitTester::CallbackType&& callback)
    {
        bool isSuccess = callback();
        RUBY_INFO("Runing test for target {}... - test {}", label, (isSuccess) ? "Passed" : "Failed");

        return (isSuccess) ? true : false;
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
        return (successTests == m_tests.size()) ? true : false;
    }
}