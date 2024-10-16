#pragma once

#include "ITest.hpp"
#include "TestsRuntime.hpp"


#define RUBY_TESTS_SUITE                         namespace Ruby::UnitTests
#define RUBY_ADD_TEST(label, test)               Ruby::Testify::TestsRuntime::GetInstance().AddTest(label, test)


#define RUBY_DEFINE_TEST(label, test)                           \
    void _##test##Test();                                       \
                                                                \
    class test##Test : public Ruby::Testify::ITest {     \
    public:                                                     \
        test##Test() {                                          \
            RUBY_ADD_TEST(label, this);                         \
        }                                                       \
                                                                \
        RubyString GetName() const override {                   \
            return label;                                       \
        }                                                       \
                                                                \
        void Run() override {                                   \
            _##test##Test();                                    \
        }                                                       \
    };                                                          \
    static test##Test sg_##test##Test##Instance;                \
                                                                \
    void _##test##Test()  


#define RUBY_TEST_CLASS(name)                   class name : public ITest
#define RUBY_TEST_METHOD(name)                  RUBY_NODISCARD void name() override

// #define RUBY_RUN_ALL_TESTS                                                          \ 
//     int main(int argc, char** argv) {                                               \
//         Ruby::Testify::TestsRuntime::GetInstance()::RunAll(argc, argv);      \
//                                                                                     \
//         return 0;                                                                   \
//     }