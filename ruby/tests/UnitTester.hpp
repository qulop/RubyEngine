#pragma once

#include <utility/StdInc.hpp>
#include <utility/RubyUtility.hpp>


namespace Ruby::Tests
{
    class UnitTester final : Singleton<UnitTester>
    {
        using CallbackType = std::function<bool(void)>;
        using TestsType = RubyHashMap<RubyString, CallbackType>;
    public:
        DEFINE_SINGLETON(UnitTester);

        void Init(void);

        void AddTest(const RubyString& label, CallbackType&& callback);

        RUBY_NODISCARD bool RunTest(const RubyString& label, CallbackType&& callback);

        bool TestAll(void);

    private:
        TestsType m_tests;
    };
}