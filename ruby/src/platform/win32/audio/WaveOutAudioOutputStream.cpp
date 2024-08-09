#include "WaveOutAudioOutputStream.hpp"

#include <utility/Logger.hpp>
#include <utility/TypeTraits.hpp>


namespace Ruby::Win32 {
    static constexpr DWORD bitsPerSample = 16;
    static constexpr DWORD samplesPerSecond = 44100;  // 44.1 kHz
    static constexpr WORD channelsNumber = 2;
    static constexpr f32 latencyInSec = 70.0f / 1000.0f;


    WaveOutAudioOutputStream::WaveOutAudioOutputStream() {
        DWORD bytesPerSec = (bitsPerSample * samplesPerSecond * channelsNumber) / 8;

        WAVEFORMATEX format = {
            .wFormatTag = WAVE_FORMAT_PCM,
            .nChannels = channelsNumber,
            .nSamplesPerSec = static_cast<WORD>(samplesPerSecond),
            .nAvgBytesPerSec = bytesPerSec,
            .nBlockAlign = (channelsNumber * bitsPerSample) / 8,
            .wBitsPerSample = static_cast<WORD>(bitsPerSample),
            .cbSize = 0
        };

        if (waveOutOpen(&m_waveOut, WAVE_MAPPER, &format, NULL, NULL, NULL) != MMSYSERR_NOERROR) {
            RUBY_ERROR("WaveOutAudioOutputStream::WaveOutAudioOutputStream() : Failed to open audio output device -- waveOutOpen() != MMSYSERR_NOERROR");
            return; // ???
        }

        u32 waveBufferSize = static_cast<u32>(roundf(bytesPerSec * latencyInSec));
        for (size_t i = 0; i < std::size(m_waveBuffers); i++) {
            VOID* allocatedMemory = VirtualAlloc(nullptr, waveBufferSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
            if (!allocatedMemory)
                RUBY_ERROR("WaveOutAudioOutputStream::WaveOutAudioOutputStream() : Failed to allocate memory via VirtualAlloc()");

            m_waveBuffers[i].header.lpData = static_cast<LPSTR>(allocatedMemory);
        }


        RUBY_SWITCH_BOOL(m_isInitialized);
    }


    void WaveOutAudioOutputStream::Open() {
        RUBY_NOT_IMPLEMENTED;
    }

    void WaveOutAudioOutputStream::Close() {
        RUBY_NOT_IMPLEMENTED;
    }


    bool WaveOutAudioOutputStream::IsInitialized() const {
        RUBY_NOT_IMPLEMENTED;

        return false;
    }

    void WaveOutAudioOutputStream::SetVolume(f64 volume) {
        RUBY_NOT_IMPLEMENTED;
    }

    void WaveOutAudioOutputStream::ResetVolume() {
        RUBY_NOT_IMPLEMENTED;
    }

    f64 WaveOutAudioOutputStream::GetVolume(f64 volume) const {
        RUBY_NOT_IMPLEMENTED;

        return 0.0f;
    }


    WaveOutAudioOutputStream::~WaveOutAudioOutputStream() {

    }
}