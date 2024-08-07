#pragma once

#include <utility/TypeTraits.hpp>
#include <audio/IAudioOuputStream.hpp>

#include <Windows.h>
#include <mmeapi.h>


namespace Ruby::Win32 {
    struct SoundBackend {
        bool isInitialized = false;

        u32 channelsCount = 2;
        u32 samplesRate = 0;
        WaveBuffer waveBuffers[64];

        // SoundBackend();
    };


    class WaveOutAudioOutputStream : public IAudioOutputStream {
    public:
        WaveOutAudioOutputStream();

        void Open() override;
        void Close() override;

        bool IsInitialized() const override;

        void SetVolume(f64 volume) override;
        void ResetVolume() override;
        f64 GetVolume(f64 volume) const override;

    private:
        bool m_isInitialized = false;

        HWAVEOUT m_waveOut = {};
        struct {
            bool isPrepared = false;
            WAVEHDR header = {};
        } m_waveBuffers[64];
    };
}