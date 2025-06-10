#pragma once

#include <framework/utility/Utils.hpp>
#ifdef RUBY_LINUX_USED
    #include <csignal>
    #include <csetjmp>
#endif


namespace Ruby::Testify {
    namespace Details::Asserts {
        template<typename Tx, typename Ty>
        void compareAssert(Tx&& exp, Ty&& act,
                           const char* strExpected, const char* strActual, bool equalOp=true) {
            bool condition = (equalOp) == (exp == act);
            if (condition)
                return;

            auto* equalitySign = (equalOp) ? "==" : "!=";
            auto msg = std::format("\"{} {} {}\": expected {}, but got {}",
                strExpected, equalitySign, strActual,
                std::forward<Tx>(exp), std::forward<Ty>(act));

            throw AssertionError{ msg.c_str() };
        }
    }


    template<typename Tx, Concepts::ContainerSTL Cont>
    void assertIn(Tx&& tx, Cont&& cont) {
        for (auto it = cont.begin(); it != cont.end(); it++)
            if (*it == tx)
                return;
        
        throw AssertionError{
            std::format("{} doesn't contains in the specified container", tx).c_str() };
    }
}

//#if defined(RUBY_WIN32_USED)
//    #define RUBY_NO_SEGFAULTS_BEGIN_IMPL()    __try {
//    #define RUBY_NO_SEGFAULTS_END_IMPL()            \
//        }                                           \
//        __except(EXCEPTION_EXECUTE_HANDLER) {       \
//            throw SegfaultError{};                  \
//        }
//#elif defined(RUBY_LINUX_USED)
//    #define RUBY_NO_SEGFAULTS_BEGIN_IMPL() \
//        if (segsetjmp(Ruby::Testify::Details::Asserst::jmpBuf, 1) == 0) { \
//            signal(SIGSEGV, si)
//    #define RUBY_NO_SEGFAULTS_END_IMPL()      \
//        }                                           \
//        __except(EXCEPTION_EXECUTE_HANDLER) {       \
//            throw SegfaultError{};                  \
//        }
//#endif



#define RUBY_TESTS_ASSERT_EQ(exp, act)          \
    Ruby::Testify::Details::Asserts::compareAssert(exp, act, #exp, #act)
#define RUBY_TESTS_ASSERT_NEQ(exp, act)         \
    Ruby::Testify::Details::Asserts::compareAssert(exp, act, #exp, #act, false)

#define RUBY_TESTS_ASSERT_TRUE(cond)            \
    Ruby::Testify::throwIfFalse(cond, "The condition doesn't evaluate to false")
#define RUBY_TESTS_ASSERT_FALSE(cond)           \
    Ruby::Testify::throwIfFalse(!cond, "The condition doesn't evaluate to false")

//#define RUBY_TESTS_NO_SEGFAULTS_BEGIN()  RUBY_NO_SEGFAULTS_BEGIN_IMPL()
//#define RUBY_TESTS_NO_SEGFAULTS_END()  RUBY_NO_SEGFAULTS_END_IMPL()

#define RUBY_TESTS_ASSERT_IS_INSTANCE(Tx, Ty)   \
    Ruby::Testify::throwIfFalse(std::is_base_of_v<Tx, Ty>, "Two types isn't equal")

#define RUBY_TESTS_ASSERT_IN(target, cont)        \
    Ruby::Testify::assertIn(target, cont)

#define RUBY_TESTS_ASSERT_MUST_ABORT(exp)   exp
