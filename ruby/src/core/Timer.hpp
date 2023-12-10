#include <chrono>


namespace Ruby::RubyTime
{
    namespace chrono = std::chrono;

    using TimePoint = chrono::time_point<chrono::system_clock, chrono::duration<double, std::milli>>;
    using TimeRep   = TimePoint::rep;


    inline TimeRep getCurrentTimeRep(void)
    {
        TimePoint now = chrono::system_clock::now();

        return now.time_since_epoch().count();
    }

}