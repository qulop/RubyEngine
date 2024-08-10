#pragma once

#include <utility/Definitions.hpp>


namespace Ruby {
	struct AudioParams {
		u32 bitsPerSample = 16;
		u32 samplesPerSecond = 44100; // 44.1 kHz
		u16 channelsNumber = 2;
		f32 latencyInSec = 70.0f / 1000.0f;

		const u32 bytesPerSecond = (bitsPerSample * samplesPerSecond * channelsNumber) / 8;
		const u32 buffersNumber = 64;


		AudioParams() = default;
		AudioParams(u32 bitsPerSample, u32 samplesPerSecond, u16 channelsNumber, f32 latencyInSec, u32 buffersNumber) :
			bitsPerSample(bitsPerSample),
			samplesPerSecond(samplesPerSecond),
			channelsNumber(channelsNumber),
			latencyInSec(latencyInSec),
			buffersNumber(buffersNumber)
		{}
	};
}