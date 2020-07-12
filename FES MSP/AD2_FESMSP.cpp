#include "AD2_FESMSP.h"

void AD2_FESMSP::rampPotentiometer(float seconds, unsigned char* direction)
{
	// switch for waveform generator output
	FDwfAnalogOutConfigure(hdwf, ev::analog::CHANNEL, 1);

	for (int i = 0; i <= ev::digiPot::steps; ++i) {
		FDwfDigitalSpiWrite(hdwf, 0, 8, direction, 1);
		Sleep(seconds / ev::digiPot::steps);
	}
}

void AD2_FESMSP::init()
{
    FDwfDigitalOutInternalClockInfo(hdwf, &hzSys);

    // enable and set supply channel to 5V
    FDwfAnalogIOChannelNodeSet(hdwf, 0, 0, 1);
    FDwfAnalogIOChannelNodeSet(hdwf, 0, 1, ev::ad2::SUPPLY_VOLTAGE);

    FDwfAnalogIOEnableSet(hdwf, true);
    FDwfAnalogOutCustomAMFMEnableSet(hdwf, ev::analog::CHANNEL, true);
    FDwfAnalogOutNodeEnableSet(hdwf, ev::analog::CHANNEL, AnalogOutNodeCarrier, true);
    FDwfAnalogOutNodeFunctionSet(hdwf, ev::analog::CHANNEL, AnalogOutNodeCarrier, funcSquare);
    FDwfAnalogOutNodeAmplitudeSet(hdwf, ev::analog::CHANNEL, AnalogOutNodeCarrier, ev::analog::CARRIER_AMP);
    FDwfAnalogOutNodeFrequencySet(hdwf, ev::analog::CHANNEL, AnalogOutNodeCarrier, ev::analog::CARRIER_AMP);
    FDwfAnalogOutNodeEnableSet(hdwf, ev::analog::CHANNEL, AnalogOutNodeAM, true);
    FDwfAnalogOutNodeFunctionSet(hdwf, ev::analog::CHANNEL, AnalogOutNodeAM, funcPulse);
    FDwfAnalogOutNodeAmplitudeSet(hdwf, ev::analog::CHANNEL, AnalogOutNodeAM, ev::analog::AM_AMP);
    FDwfAnalogOutNodeFrequencySet(hdwf, ev::analog::CHANNEL, AnalogOutNodeAM, ev::analog::AM_FREQ);
    FDwfAnalogOutNodeOffsetSet(hdwf, ev::analog::CHANNEL, AnalogOutNodeAM, ev::analog::AM_OFFSET);
    FDwfAnalogOutConfigure(hdwf, ev::analog::CHANNEL, true);

    // configure SPI on AD2
    FDwfDigitalSpiReset(hdwf);
    FDwfDigitalSpiFrequencySet(hdwf, 9600);
    FDwfDigitalSpiClockSet(hdwf, ev::spi::SCK);
    FDwfDigitalSpiDataSet(hdwf, 0, ev::spi::SDIO);
    FDwfDigitalSpiModeSet(hdwf, 0);
    FDwfDigitalSpiOrderSet(hdwf, 1);
    FDwfDigitalSpiSelect(hdwf, ev::spi::CS, 0);
    Sleep(1.0);
    FDwfDigitalSpiWrite16(hdwf, 0, 16, ev::spi::ZERO, 1);

    // enable both analog channels
    FDwfAnalogInChannelEnableSet(hdwf, 0, true);
    FDwfAnalogInChannelEnableSet(hdwf, 1, true);

    // set 0V offset
    FDwfAnalogInChannelOffsetSet(hdwf, -1, 0);

    // set 10V pk2pk range
    FDwfAnalogInChannelRangeSet(hdwf, -1, ev::ad2::SUPPLY_VOLTAGE * 2);

    toggleMasterSwitches(false);
}
