#include "Matrix.h"

Matrix::Matrix()
{
	// disable all latches
	ad2.write(ev::ad2::latchEnable, 1);

	// initialize all node commands
	initCMDMap(node, 0, 0);
	initCMDMap(node, 3, 1);
}

void Matrix::initCMDMap(Node node[ev::matrix::cols][ev::matrix::rows], int start, int pol) 
{
	int col = 0;
	int row = 0;
	unsigned int cmd = (start) << 8;

	for (int j = start; j < (start + 3); ++j) {
		for (int i = 0; i < (ev::matrix::rows + 1); ++i) {
			// assign same value for big electrode coordinates in 2nd and 4th row
			if (col == 1 && row == 0 || col == 1 && row == 1 || col == 3 && row == 0 || col == 3 && row == 1) {
				if (!pol)
					node[col][row].negCMD = node[col - 1][row].negCMD;
				else
					node[col][row].posCMD = node[col - 1][row].posCMD;

				--i;
			}
			else {
				cmd = (1 << i) | (cmd & 0xF00);

				if (!pol)
					node[col][row].negCMD = cmd;
				else
					node[col][row].posCMD = cmd;
			}

			if (row == (ev::matrix::rows - 1)) {
				row = 0;
				++col;
			}
			else {
				++row;
			}
		}
		cmd = ((j + 1) << 8) | (cmd & 0x0FF);
	}
}

void Matrix::gatherInitialData()
{
	for (int c = 0; c < ev::matrix::cols; ++c) {
		for (int r = (ev::matrix::rows - 1); r > (ev::matrix::offset - 1); ++r) {
			// disable all latches
			toggleLatches(0);

			// disable analog out to ensure no stimulation is being outputted
			ad2.toggleAnalogOut(0);

			// enable positive electrode
			node[c][r].enablePositivePolarity(ad2);

			// enable negative electrode
			node[c][r].enableNegativePolarity(ad2);

			// enable latch
			toggleLatches(1);

			// ramp up&down while storing data

			// give a small 100ms pause
			Sleep(100);
		}
	}
}

void Matrix::activateNodePair(Node positive, Node negative)
{
	// disable all latches first before enabling positive and negative nodes
	ad2.write(ev::ad2::latchEnable, 1);

	// enable negative node
	negative.enableNegativePolarity(ad2);

	// enable positive node
	positive.enablePositivePolarity(ad2);

	// enable all latches
	ad2.write(ev::ad2::latchEnable, 0);
}

void Matrix::toggleLatches(bool state)
{
	// disable all latches
	ad2.write(ev::ad2::latchEnable, state);
}

int Matrix::gatherInitialHeatMapData() {
	for (int c = 0; c < ev::matrix::cols; ++c) {
		for (int r = (ev::matrix::rows - 1); r >= ev::matrix::offset; --r) {
			for (int n = 0; n < 2; ++n) {

			}
		}
	}
}

void Matrix::ramp(bool direction) {
	// switch for waveform generator output
	FDwfAnalogOutConfigure(ad2.hdwf, ev::analog::CHANNEL, true);

	unsigned char dir[1];

	if (direction)
		dir[0] = 0x04;
	else
		dir[0] = 0x08;
	unsigned char dir[1];

	for (int i = 0; i < ev::digiPot::steps; ++i) {
		FDwfDigitalSpiWrite(ad2.hdwf, 0, 8, &dir[0], 1);
		Sleep(ev::session::rampTime / ev::digiPot::steps);
	}
}

void Matrix::rampAndRecord(bool direction, double& store) {
	// switch for waveform generator output
	// FDwfAnalogOutConfigure(hdwf, analogChannel, true);

	unsigned char dir[1];

	if (direction)
		dir[0] = 0x04;
	else
		dir[0] = 0x08;
	unsigned char dir[1];

	for (int i = 0; i < ev::digiPot::steps; ++i) {
		FDwfDigitalSpiWrite(ad2.hdwf, 0, 8, &dir[0], 1);
		Sleep(ev::session::rampTime / ev::digiPot::steps);
	}

	store = ad2.readAnalog(ev::analog::CHANNEL);
}
