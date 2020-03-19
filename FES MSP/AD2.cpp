#include "AD2.h"

AD2::~AD2()
{
	FDwfDeviceClose(hdwf);
}

void AD2::init()
{
	// power supply config
	FDwfAnalogIOChannelNodeSet(hdwf, 0, 0, 1); 				// enable analog io positive supply channel
	FDwfAnalogIOChannelNodeSet(hdwf, 0, 1, ad2_vSupply); 	// sets analog io positive supply channel to 5V

	// analog in config
	FDwfAnalogInChannelEnableSet(hdwf, ad2_flexChannel, true);		// enable analog channel in for flex sensor reading
	FDwfAnalogInChannelEnableSet(hdwf, ad2_potChannel, true); 		// enable analog in channel for potentiometer reading
	FDwfAnalogInChannelOffsetSet(hdwf, -1, 0);						// set 0V offset for both analog in channels
	FDwfAnalogInChannelRangeSet(hdwf, -1, ad2_vSupply * 2);			// set 10V (voltage supply * 2) pk2pk range for both channels

	// analog out (waveform generator) config
	FDwfAnalogOutNodeEnableSet(hdwf, ad2_aOutChannel, AnalogOutNodeCarrier, true); 					// enable channel and node (carrier) 		
	FDwfAnalogOutNodeFunctionSet(hdwf, ad2_aOutChannel, AnalogOutNodeCarrier, funcSquare);			// set output function for carrier
	FDwfAnalogOutNodeAmplitudeSet(hdwf, ad2_aOutChannel, AnalogOutNodeCarrier, ad2_aCarrierAmp);	// set amplitude for carrier
	FDwfAnalogOutNodeFrequencySet(hdwf, ad2_aOutChannel, AnalogOutNodeCarrier, ad2_aCarrierFreq); 	// set frequency for carrierr
	FDwfAnalogOutNodeEnableSet(hdwf, ad2_aOutChannel, AnalogOutNodeAM, true);						// enable channel and node (AM)
	FDwfAnalogOutNodeFunctionSet(hdwf, ad2_aOutChannel, AnalogOutNodeAM, funcPulse);				// set output function for AM
	FDwfAnalogOutNodeAmplitudeSet(hdwf, ad2_aOutChannel, AnalogOutNodeAM, ad2_aAMAmp);				// set amplitude for AM
	FDwfAnalogOutNodeFrequencySet(hdwf, ad2_aOutChannel, AnalogOutNodeAM, ad2_aAMFreq);				// set frequency for AM
	FDwfAnalogOutNodeOffsetSet(hdwf, ad2_aOutChannel, AnalogOutNodeAM, ad2_aAMOffset);				// set offset for AM

	// digital out config
	//  unsigned int activePins = 0x0000|1<<es_0|1<<es_1|1<<es_2|1<<es_3|1<<es_4|1<<es_5|1<<es_6|1<<es_7|1<<ls_0|1<<ls_1|1<<ls_2;
	//	FDwfDigitalIOOutputEnableSet(hdwf, activePins);

	// SPI config 
	FDwfDigitalSpiFrequencySet(hdwf, spi_frequency); 	// set SPI frequency
	FDwfDigitalSpiClockSet(hdwf, spi_SCK); 				// set DIO channel to use for spi clock
	FDwfDigitalSpiDataSet(hdwf, 0, spi_SISO);			// set DIO channels to use for SPI data
	FDwfDigitalSpiModeSet(hdwf, 0);						// set SPI mode
	FDwfDigitalSpiOrderSet(hdwf, 1);					// set SPI bit orde, 1 = MSB
	FDwfDigitalSpiSelect(hdwf, spi_CS, 0);				// set SPI CS signal    

	//unsigned short cmd = 0x00FF;
	//FDwfDigitalSpiWrite16(hdwf, 0, 16, &cmd, 1);		// initialize digital potentiometer   

	Sleep(100);
}

void AD2::writeDIO(unsigned short int cmd)
{
	// 11 bits in total
	// leading 3 bits are latch select, following 8 bits are electrode select
	FDwfDigitalIOOutputSet(hdwf, cmd);
}

double AD2::readAIO(int channel)
{
	double temp;

	FDwfAnalogInStatus(hdwf, false, NULL);
	FDwfAnalogInStatusSample(hdwf, channel, &temp);

	return temp;
}

void AD2::writeSPI(unsigned char* cmd)
{
	FDwfDigitalSpiWrite(hdwf, 0, 8, cmd, 1);
}