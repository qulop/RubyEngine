#include "IAudioOutputStream.hpp"

#include <platform/Platform.hpp>
#include <win32/audio/WaveOutAudioOutputStream.hpp>


namespace Kiwi {
	SharedPtr<IAudioOutputStream> IAudioOutputStream::Create(const AudioParams& params) {
        if constexpr (GetCurrentPlatform() == ECurrentPlatform::WINDOWS) {
            return MakeShared<Win32::WaveOutAudioOutputStream>(params);
        }
	    else {
            std::unreachable();
        }
    }
}