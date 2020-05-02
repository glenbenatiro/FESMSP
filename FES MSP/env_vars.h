#pragma once
#ifndef ENV_VARS_H
#define ENV_VARS_H

//#define KEY_UP 72
//#define KEY_DOWN 80
//#define KEY_LEFT 75
//#define KEY_RIGHT 77
//#define ENTER 13
//#define BACKSPACE 8

namespace ev 
{
	inline constexpr int COLS{ 4 };
	inline constexpr int ROWS{ 7 };

	// --- global values config
	// for AD2
	inline constexpr double ad2_vSupply = 5.0;
	inline constexpr int ad2_flexChannel = 0;
	inline constexpr int ad2_potChannel = 1;
	inline constexpr int ad2_aOutChannel = 0;
	inline constexpr double ad2_aCarrierFreq = 10e3;
	inline constexpr double ad2_aCarrierAmp = 1.65;
	inline constexpr double ad2_aAMFreq = 50.0;
	inline constexpr int ad2_aAMAmp = 100;
	inline constexpr int ad2_aAMOffset = -100;

	// for SPI
	inline constexpr double spi_frequency = 10000;
	inline constexpr int spi_CS = 0;
	inline constexpr int spi_SCK = 1;
	inline constexpr int spi_SISO = 2;

	// for ckt
	// electrode select
	inline constexpr int es_0 = 3;
	inline constexpr int es_1 = 4;
	inline constexpr int es_2 = 5;
	inline constexpr int es_3 = 6;

	inline constexpr int es_4 = 7;
	inline constexpr int es_5 = 8;
	inline constexpr int es_6 = 9;
	inline constexpr int es_7 = 10;

	// latch select
	inline constexpr int ls_0 = 11;
	inline constexpr int ls_1 = 12;
	inline constexpr int ls_2 = 13;

	// for program
	inline constexpr double p_rampTime = 3.0;
	inline constexpr 	int matrix_xStep = 6;
	inline constexpr 	int matrix_yStep = 3;

	// --- global variables
	// for AD2
	inline constexpr double hzSys = 0;
}

#endif // ENV_VARS_H