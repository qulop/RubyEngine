#pragma once

#include <utility/Definitions.hpp>

#include <types/StdInc.hpp>


namespace Ruby::ThisThread {
    // Executes the x86 `pause` assembly instruction
    // For more information: https://www.felixcloutier.com/x86/pause
	void cpuPause();

    //void mFence();
}


namespace Ruby::Sync {
    using Mutex = std::mutex;


    class SpinWait {
    public:
        SpinWait() = default;

    public:
        SpinWait(const SpinWait&) = delete;
        SpinWait(SpinWait&&) = delete;
    
        SpinWait& operator=(const SpinWait&) = delete;
        SpinWait& operator=(SpinWait&&) = delete;
    
    public:
        void Spin();

        void Reset();

        RUBY_NODISCARD bool IsSpinLimitReached() const;
        RUBY_NODISCARD bool ShouldPark() const;
    
    private:
        static constexpr size_t s_spinLimit = 8;
        static constexpr size_t s_yieldLimit = 16;
    
        size_t m_spinCount = 0;
    };


    class AdaptiveMutex {
    public:
        AdaptiveMutex() = default;

        AdaptiveMutex(const AdaptiveMutex&) = delete;
        AdaptiveMutex(AdaptiveMutex&&) = delete;
    
        AdaptiveMutex& operator=(const AdaptiveMutex&) = delete;
        AdaptiveMutex& operator=(AdaptiveMutex&&) = delete;

    public:
        void Lock();
        void Unlock();

        void lock();
        void unlock();

    private:
        Mutex m_mutex;
    };
}