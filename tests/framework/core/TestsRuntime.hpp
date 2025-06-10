#pragma once

#include <types/StdInc.hpp>
#include <types/Singleton.hpp>
#include <utility/ProgramOptions.hpp>

#include "ITest.hpp"


namespace Ruby::Testify {
    class TestsRuntime final : Singleton<TestsRuntime> {
    public:
        using CallbackType = std::function<bool()>;
        using StorageType = Vector<std::pair<String, ITest*>>;

    public:
        RUBY_DEFINE_SINGLETON(TestsRuntime);

        void Register(String label, ITest* test);

        static void RunTest(const String& label, ITest* test);
        RUBY_NODISCARD i32 RunAllTests(const ProgramOptions& opts) const;

        RUBY_NODISCARD StorageType GetAllTestsCopy() const;
        RUBY_NODISCARD const StorageType& GetAllTestsRef() const;

    private:
        RUBY_NODISCARD i32 RunAllRegisteredTests() const;
        void RunFromCommandLine(ProgramOptions&& args);

        RUBY_NODISCARD i32 TestAll(const StorageType& testsStorage) const;

    private:
        StorageType m_tests;
    };


    RUBY_FORCEINLINE TestsRuntime& getTestsRuntime() {
        return TestsRuntime::GetInstance();
    }
}