#include "IAudioOutputStream.hpp"

#include <platform/Platform.hpp>
#include <platform/win32/audio/WaveOutAudioOutputStream.hpp>

#include <utility/RubyUtility.hpp>
#include <utility/Logger.hpp>


namespace Ruby {
	Ptr<IAudioOutputStream> IAudioOutputStream::Create() {
        if (getPlatform() == PLATFORM_WINDOWS)  // NOLINT
            return MakePtr<Win32::WaveOutAudioOutputStream>();
        RUBY_CRITICAL("IAudioOutputStream::Create() : Failed to create instance of IAudioOutputStream -- your platform isn't supported for now");

        return nullptr; // Unreachable code
    }
}