#pragma once

#include <utility/Definitions.hpp>


namespace Ruby {
    interface IAudioOutputStream {
    public:
        virtual void Open() = 0;
        virtual void Close() = 0;

        RUBY_NODISCARD virtual bool IsInitialized() const = 0;

        virtual void SetVolume(f64 volume) = 0;
        virtual void ResetVolume() = 0;
        RUBY_NODISCARD virtual f64 GetVolume(f64 volume) const = 0;

        virtual ~IAudioOutputStream() = default;

    public:
        static Ptr<IAudioOutputStream> Create();
    };
}