#pragma once

#include <utility/TypeTraits.hpp>
#include <audio/IAudioOutputStream.hpp>

#include <Windows.h>
#include <mmeapi.h>


namespace Ruby::Win32 {
    class WaveOutAudioOutputStream : public IAudioOutputStream {
    public:
        WaveOutAudioOutputStream();

        void Open() override;
        void Close() override;

        RUBY_NODISCARD bool IsInitialized() const override;

        void SetVolume(f64 volume) override;
        void ResetVolume() override;
        RUBY_NODISCARD f64 GetVolume(f64 volume) const override;


        ~WaveOutAudioOutputStream() override;

    private:
        bool m_isInitialized = false;

        HWAVEOUT m_waveOut = {};
        struct alignas(std::max_align_t) {
            WAVEHDR header = {};
            bool isPrepared = false;
        } m_waveBuffers[64];
    };
}