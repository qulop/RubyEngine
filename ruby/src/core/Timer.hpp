#include <chrono>


namespace Ruby::RubyTime
{
    using namespace std::chrono;

    using SteadyTimePoint   = time_point<steady_clock, duration<double, std::milli>>;
    using TimeRep           = SteadyTimePoint::rep;


    inline TimeRep getCurrentTimeRep(void)
    {
        SteadyTimePoint now = steady_clock::now();

        return now.time_since_epoch().count();
    }
}