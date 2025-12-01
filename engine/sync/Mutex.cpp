#include "Mutex.hpp"

#if defined(KIWI_MSVC_USED)
	#include <intrin.h>
#endif


namespace Kiwi::ThisThread {
    void CpuPause() {
		#if defined(KIWI_GCC_USED) || defined(KIWI_CLANG_USED)
			asm volatile("pause\n\t" : : : "memory");
		#elif defined(KIWI_MSVC_USED)
			_mm_pause();
		#else
			static_assert(Traits::LazyEval<Traits::AlwaysFalse>::value, "You're using unsupported compiler!");
		#endif
    }
}


namespace Kiwi::Sync {
    void SpinWait::Spin() {
        if (m_spinCount < SpinWait::s_spinLimit) {
            for (size_t i = 0; i < ((size_t)1 << m_spinCount); i++) {
                ThisThread::CpuPause();
            }
        }
        else {
            std::this_thread::yield();
        }

        ++m_spinCount;
    }

    void SpinWait::Reset() {
        m_spinCount = 0;
    }

    bool SpinWait::IsSpinLimitReached() const {
        return m_spinCount >= SpinWait::s_spinLimit;
    }

    bool SpinWait::ShouldPark() const {
        return m_spinCount >= SpinWait::s_yieldLimit;
    }



    void AdaptiveMutex::Lock() {
        SpinWait spinWait;

        while (!spinWait.ShouldPark()) {
            spinWait.Spin();
        }
    }

    void AdaptiveMutex::Unlock() {
        
    }


    void lock();
    void unlock();
}