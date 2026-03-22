#pragma once

#include <common/PCH.hpp>


namespace Kiwi {
    constexpr auto MEM_ORDER_RELAXED = std::memory_order::relaxed;
    constexpr auto MEM_ORDER_SEQ_CST = std::memory_order::seq_cst;
    constexpr auto MEM_ORDER_ACQUIRE = std::memory_order::acquire;
    constexpr auto MEM_ORDER_RELEASE = std::memory_order::release;
    constexpr auto MEM_ORDER_CONSUME = std::memory_order::consume;


    template<typename T>
    using Atomic = std::atomic<T>;

    using AtomicBool = Atomic<bool>;

    using AtomicU32 = Atomic<u32>;
    using AtomicU64 = Atomic<u64>;

    using AtomicI32 = Atomic<i32>;
    using AtomicI64 = Atomic<i64>;

    using AtomicF32 = Atomic<f32>;
    using AtomicF64 = Atomic<f64>;
}