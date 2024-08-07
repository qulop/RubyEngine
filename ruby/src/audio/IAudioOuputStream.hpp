#include <utility/Definitions.hpp>


namespace Ruby {
    interface IAudioOutputStream {
        virtual void Open() = 0;
        virtual void Close() = 0;

        virtual bool IsInitialized() const = 0;

        virtual void SetVolume(f64 volume) = 0;
        virtual void ResetVolume() = 0;
        virtual f64 GetVolume(f64 volume) const = 0;
    };
}