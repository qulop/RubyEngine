#pragma once

#include <tests/framework/utility/Utils.hpp>


namespace Ruby::Testify {
    namespace Details::Asserts {
        template<typename Tx, typename Ty>
        void compareAssert(Tx&& exp, Ty&& act, const char* strExpr, bool equalOp=true) {
            bool condition = (equalOp) ? (exp == act) : (exp != act);
            if (condition)
                return;

            auto msg = std::format("{}: expected {}, but got {}", 
                strExpr, std::forward<Tx>(exp), std::forward<Ty>(act));
            throw AssertionError{ msg.c_str() };
        }
    }


    template<typename Tx, Concepts::STLContainterLike Cont>
    void assertIn(Tx&& tx, Cont&& cont, const char* strExpr) {
        auto&& it = cont.begin();
        for (it; it != cont.end(); it++)
            if (*it == tx)
                return;
        
        throw AssertionError{ std::format("{} doesn't contains in the ") }
    }
}


#define RUBY_TESTS_ASSERT_EQ(exp, act) Ruby::Testify::Details::Asserts::compareAssert(exp, act, #act);
#define RUBY_TESTS_ASSERT_NEQ(exp, act) Ruby::Testify::Details::Asserts::compareAssert(exp, act, #act, false);

#define RUBY_TESTS_ASSERT_TRUE(cond)    \
    Ruby::Testify::throwIfFalse(cond, "The condition doesn't evalueate to false");
    
#define RUBY_TESTS_ASSERT_FALSE(cond)   \
    Ruby::Testify::throwIfFalse(!cond, "The condition doesn't evalueate to false");

#define RUBY_TESTS_ASSERT_IS_INSTANCE(Tx, Ty)   \
    Ruby::Testify::throwIfFalse(std::is_base_of_v<Tx, Ty>, "Two types isn't equal")
