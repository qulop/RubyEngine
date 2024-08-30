#pragma once

#include <types/StdInc.hpp>
#include <utility/RubyUtility.hpp>

#include "ITest.hpp"


namespace Ruby::Testify {
    class TestsRuntime final : Singleton<TestsRuntime> {
    public:
        using CallbackType = std::function<bool()>;
        using StorageType = RubyVector<std::pair<RubyString, ITest*>>;

    public:
        RUBY_DEFINE_SINGLETON(TestsRuntime);

        void AddTest(RubyString label, ITest* test);

        void RunTest(RubyString label, ITest* test);

        void RunAllRegistredTests();
        void RunFromCommandLine(int argc, const char** argv);

        StorageType GetAllTestsCopy() const;
        const StorageType& GetAllTestsRef() const;

    private:
        void TestAll(const StorageType& testsStorage);

    private:
        StorageType m_tests;
    };
}