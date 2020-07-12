#pragma once
#ifndef ENV_VARS_H
#define ENV_VARS_H

#include <string>

namespace ev
{
	namespace session {
		inline constexpr int intervalTime = 1000;	// in milliseconds
		inline constexpr int totalSessionTime = 5;	// in minutes

		inline constexpr double rampTime = 3000; // in milliseconds
	}

	namespace keymap {
		inline constexpr int up = 119;
		inline constexpr int down = 115;
		inline constexpr int left = 97;
		inline constexpr int right = 100;
		inline constexpr int enter = 101;
		inline constexpr int backspace = 8;
	}

	namespace matrix {
		inline constexpr int cols = 4;
		inline constexpr int rows = 7;
		inline constexpr int offset = 2;
	}

	namespace ad2 {
		inline constexpr double SUPPLY_VOLTAGE = 5.0;
		inline const std::string dataBus = "13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3";
		inline constexpr int latchEnable = 14;
	}

	namespace analog {
		inline constexpr int CHANNEL = 0;
		inline constexpr double CARRIER_FREQ = 10e3;
		inline constexpr double CARRIER_AMP = 1.65;
		inline constexpr double AM_FREQ = 50.0;
		inline constexpr int AM_AMP = 100;
		inline constexpr int AM_OFFSET = -100;
	}

	namespace digiPot {
		inline constexpr int CS = 0;
		inline constexpr int SCK = 1;
		inline constexpr int SDIO = 2;
		inline constexpr int steps = 256;

		enum direction {
			up = 0x04,
			down = 0x08,
		};
	}

	namespace spi {
		inline constexpr double FREQ = 10e3;
		inline constexpr int CS = 0;
		inline constexpr int SCK = 1;
		inline constexpr int SDIO = 2;
		inline unsigned short ZERO[1] = { 0x0000 };
	}
}

#endif // ENV_VARS_H