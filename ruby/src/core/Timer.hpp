#include <chrono>


namespace Ruby::RubyTime
{
    namespace time = std::chrono;

    using SteadyTimePoint   = time::time_point<time::steady_clock, time::duration<double, std::milli>>;
    using TimeRep           = SteadyTimePoint::rep;


    inline TimeRep getCurrentTimeRep()
    {
        SteadyTimePoint now = time::steady_clock::now();

        return now.time_since_epoch().count();
    }
}