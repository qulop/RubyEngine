// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! DONT TOUCH THIS FILE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#pragma once

#include "STL.hpp"

#include <utility/Definitions.hpp>
#include <TypeTraits.hpp>


namespace Ruby::Std {
    enum class SharedPtrUsagePolicy {
        MANUAL_CLEANING,
        AUTO_CLEANING
    };



    template<typename Tx>
    class SharedPtr : public STL::ISmartPoitner<Tx> {
    public:
        using ElementType = element_type;

    public:
        ElementType* Get() const {

        }

        i32 GetCount() const {

        }

    public: // STL-style methods
        void reset() override {

        }

        void swap(ISmartPoitner* other) override {

        }


        element_type* get() const override {
            return Get();
        }


        element_type& operator*() const override {

        }

        element_type* operator->() const override {

        }


        element_type& operator[](ptrdiff_t idx) const override {

        }


        i32 use_count() const override {
            return GetCount();
        }

        explicit operator bool() const override {
            return m_ptr != nullptr;
        }

    private: 
        element_type* m_ptr = nullptr;
    };
}