#include <chrono>


namespace Ruby::Time {
    namespace time = std::chrono;

    using SteadyTimePoint   = time::time_point<time::steady_clock, time::duration<double, std::milli>>;
    using TimeRep           = SteadyTimePoint::rep;


    inline TimeRep getCurrentTimeRep() {
        SteadyTimePoint now = time::steady_clock::now();

        return now.time_since_epoch().count();
    }


    template<typename ClockType = time::steady_clock, 
            typename TimePoint = ClockType::time_point>
    class StopWatch {
        using Duration = ClockType::duration;

    public:
        StopWatch() : 
            m_begin(Now())
        {}

        static TimePoint Now() {
            return TimePoint::now();
        }

        Duration Elapsed() {
            return Now() - m_begin;
        }

        Duration FetchRestart() {
            auto tmp = m_begin;
            Restart();
            return tmp;
        }

        void Restart() {
            m_begin = Now();
        }

    private:
        TimePoint m_begin;
    };
}