#pragma once

#include "core/ITest.hpp"
#include "core/TestsRuntime.hpp"
#include "core/Asserts.hpp"


#include "utility/Utils.hpp"
#include "utility/Exceptions.hpp"


#define RUBY_TESTS_SUITE                                namespace Ruby::UnitTests
#define RUBY_REGISTER_TEST(label, test)                 Ruby::Testify::TestsRuntime::GetInstance().Register(label, test)


#define RUBY_DEFINE_TEST(label, test)                           \
    void _##test##Test();                                       \
                                                                \
    class test##Test : public Ruby::Testify::ITest {            \
    public:                                                     \
        test##Test() {                                          \
            RUBY_REGISTER_TEST(label, this);                    \
        }                                                       \
                                                                \
        String GetName() const override {                   \
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


#define RUBY_RUN_ALL_TESTS(opts)                                \
        Ruby::Testify::getTestsRuntime().RunAllTests(opts);
