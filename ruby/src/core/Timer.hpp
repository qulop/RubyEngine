#include <types/StdInc.hpp>


namespace Ruby::Time {
    namespace time = std::chrono;

    using SteadyTimePoint   = time::time_point<time::steady_clock, time::duration<double, std::milli>>;
    using TimeRep           = SteadyTimePoint::rep;


    // template<typename ClockType = std::chrono::steady_clock>
    // RubyString prettifyTime(typename ClockTime::duration duration) {
    //     auto ms = time::duration_cast<time::milliseconds>(duration);
        
    // }

    template<typename ClockType = std::chrono::steady_clock>
    RUBY_FORCEINLINE typename ClockType::time_point now() {
        return ClockType::now();
    }

    RUBY_FORCEINLINE i64 getCurrentTimeRep() {
        return now().time_since_epoch().count();
    }


    template<typename ClockType = time::steady_clock, 
            typename TimePoint = ClockType::time_point>
    class StopWatch {
        using Duration = ClockType::duration;

    public:
        StopWatch() : 
            m_begin(now())
        {}

        Duration Elapsed() {
            return now() - m_begin;
        }

        Duration FetchRestart() {
            auto tmp = m_begin;
            Restart();
            return tmp;
        }

        void Restart() {
            m_begin = now();
        }

    private:
        TimePoint m_begin;
    };
}