#pragma once

#include <utility/StdInc.hpp>
#include <utility/RubyUtility.hpp>


namespace Ruby::Tests
{
    class UnitTester final : Singleton<UnitTester>
    {
        using CallbackType = std::function<bool()>;
        using TestsType = RubyHashMap<RubyString, CallbackType>;
    public:
        DEFINE_SINGLETON(UnitTester);

        void Init();

        void AddTest(const RubyString& label, CallbackType&& callback);

        static bool RunTest(const RubyString& label, CallbackType&& callback);

        void TestAll();

    private:
        TestsType m_tests;
    };
}