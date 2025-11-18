#pragma once

#include <types/StdInc.hpp>


namespace Ruby::Math {
	constexpr double PI = 3.1415926535897932384626433832795028841971693993751058209749445923; // 64 digits after floating point

	template<std::floating_point Tx>
	Tx Radians(Tx degree) {
		return degree * static_cast<Tx>(0.01745329251994329576923690768489);
	}

	template<std::floating_point Tx>
	Tx Degree(Tx radians) {
		return radians * static_cast<Tx>(57.295779513082320876798154814105);
	}

}