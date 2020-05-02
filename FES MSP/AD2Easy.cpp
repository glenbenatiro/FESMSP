#include "AD2Easy.h"

AD2Easy::~AD2Easy()
{
	FDwfDeviceClose(hdwf);
}

void AD2Easy::init()
{
	FDwfDeviceCloseAll();
}

void AD2Easy::close()
{
	FDwfDeviceClose(hdwf);
}

bool AD2Easy::isConnected() {
	if (!FDwfDeviceOpen(-1, &hdwf)) {
		return false;
	}
	else {
		return true;
	}
}

void AD2Easy::setDir(int port, bool dir)
{
	// get current direction of all ports
	unsigned int portInt = 0x0000;
	FDwfDigitalIOOutputEnableGet(hdwf, &portInt);

	// convert portInt to a binary string to easily manipulate bits
	std::string portStr = std::bitset<16>(portInt).to_string();

	// manipulate specific port to set direction
	portStr[15-port] = static_cast<char>(dir + '0');

	// change string back to unsigned int
	portInt = std::stoi(portStr, nullptr, 2);

	// call AD2 function to set direction of all ports
	FDwfDigitalIOOutputEnableSet(hdwf, portInt);
}

void AD2Easy::setDirAll(bool dir)
{
	FDwfDigitalIOOutputEnableSet(hdwf, dir ? 0xFFFF : 0x0000);
}

bool AD2Easy::read(int port)
{
	unsigned int portStates = readAll();
	return (1 & (portStates >> port));
}

unsigned int AD2Easy::readAll()
{
	unsigned int portStates = 0x0000;
	FDwfDigitalIOStatus(hdwf);
	FDwfDigitalIOOutputGet(hdwf, &portStates);
	return portStates;
}

void AD2Easy::write(int port, bool state)
{
	// read all port states
	unsigned int portStates = readAll();

	// convert x to a binary string to easily manipulate bits
	std::string portStatesStr = std::bitset<16>(portStates).to_string();

	// manipulate specific port to set state
	portStatesStr[15 - port] = static_cast<char>(state + '0');

	// change string back to unsigned int
	portStates = std::stoi(portStatesStr, nullptr, 2);

	// call AD2 function to set state of all ports
	FDwfDigitalIOOutputSet(hdwf, portStates);
}

void AD2Easy::writeAll(unsigned int cmd)
{
	FDwfDigitalIOOutputSet(hdwf, cmd);
}

void AD2Easy::write(std::string ports, unsigned int cmd)
{
	std::vector<int> vect;

	strToArr(ports, vect);
	for (int i = 0; i < vect.size(); ++i) {
		write(vect[vect.size() - 1 - i], (1 & (cmd >> i)));
	}
}

void AD2Easy::strToArr(std::string ports, std::vector<int> &x)
{
	int temp;
	std::string substr;
	std::stringstream ss(ports);


	while (ss.good()) {
		getline(ss, substr, ',');
		if (substr != " " && substr != "") {
			temp = std::stoi(substr);
			x.push_back(temp);
		}
	}
}

unsigned int AD2Easy::read(std::string ports)
{
	unsigned int val = 0x0000;
	std::vector<int> vect;

	strToArr(ports, vect);
	for (int i = 0; i < vect.size(); ++i) {
		val |= (read(vect[vect.size() - i - 1]) << i);
	}

	return val;
}

unsigned int AD2Easy::readDirAll()
{
	unsigned int portDir = 0x0000;
	FDwfDigitalIOOutputEnableGet(hdwf, &portDir);
	return portDir;
}