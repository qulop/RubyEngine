#pragma once

#include <common/Definitions.hpp>
#include <common/meta/TypeTraits.hpp>
#include <common/PCH.hpp>



namespace Kiwi {
    class Application;


    class Time {
    public:
        using ClockType = std::chrono::steady_clock;

        using DurationType = ClockType::duration;
        using DurationRepType = DurationType::rep;

        using TimePointType = ClockType::time_point;
        using TimePointRepType = TimePointType::rep;


        static_assert(std::is_trivially_copyable_v<DurationRepType> && std::is_trivially_copyable_v<TimePointRepType>);

    public:
        KIWI_NODISCARD static f32 DeltaTime();
        KIWI_NODISCARD static DurationType DeltaTimeNative();

        KIWI_NODISCARD static TimePointType Now();
        KIWI_NODISCARD static DurationType NowAsDuration();
        KIWI_NODISCARD static TimePointRepType NowAsCount();

        KIWI_NODISCARD static DurationType GetTime();

    private:
        // Can **only** be invoked from the main thread. Specifically, only from the application's main loop.
        // That's why we have the `Application` class as a friend
        static void UpdateTime();

        // Set the initialization time point,
        // which will be used as the starting point in such functions like GetTime() or GetCurrentTimePoint()
        static void SetInitializationPoint();

    private:
        friend class Application;

        struct TimeStorage {
            bool wasInitialized = false;

            TimePointType engineInitializationPoint;
            std::atomic<DurationRepType> lastFrameTime = 0;
            std::atomic<DurationRepType> deltaTime = 0;
        };

    private:
        static TimeStorage s_storage;
    };



    class StopWatch {
        using ClockType = std::chrono::steady_clock;
        using DurationType = ClockType::duration;
        using TimePointType = ClockType::time_point;

    public:
        KIWI_NODISCARD static TimePointType Now();

    public:
        StopWatch();

        KIWI_NODISCARD std::chrono::duration<f64, std::milli> GetElapsed() const;
        void Restart();

    private:
        TimePointType m_begin;
    };
}