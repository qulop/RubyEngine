#include "IAudioOutputStream.hpp"

#include <platform/Platform.hpp>
#include <win32/audio/WaveOutAudioOutputStream.hpp>

#include <types/Logger.hpp>


namespace Kiwi {
	SharedPtr<IAudioOutputStream> IAudioOutputStream::Create(const AudioParams& params) {
        if constexpr (GetCurrentPlatform() == ECurrentPlatform::WINDOWS) {
            return MakeShared<Win32::WaveOutAudioOutputStream>(params);
        }
	    else {
            KIWI_CRITICAL(
                "IAudioOutputStream::Create() : Failed to create instance of IAudioOutputStream -- your platform isn't supported for now");
            return nullptr;
        }
    }
}