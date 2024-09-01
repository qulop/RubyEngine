#pragma once

#include <types/TypeTraits.hpp>
#include <audio/IAudioOutputStream.hpp>
#include <audio/AudioParams.hpp>

#include <Windows.h>
#include <mmeapi.h>


namespace Ruby::Win32 {
    class WaveOutAudioOutputStream : public IAudioOutputStream {
    public:
        WaveOutAudioOutputStream(const AudioParams& params);

        bool Open() override;
        void Close() override;

        void SetVolume(f64 volume) override;
        void ResetVolume() override;
        RUBY_NODISCARD f64 GetVolume(f64 volume) const override;

        
        ~WaveOutAudioOutputStream() override;

    private:
        void PrepareBuffers();
        void FreeBuffers();

    private:
        const f32 m_latency = 0.0f;
        const u32 m_buffersNumber = 0;

        HWAVEOUT m_waveOut = {};
        WAVEFORMATEX m_format = {};
        WAVEHDR* m_waveBuffers = nullptr;
    };
}