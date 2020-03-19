/*
* AD2Easy
*
* A library that further abstracts common Analog Discovery 2 
* functions for faster coding and project implementation.
*
* Created by Louille Glen Benatiro. April 2020.
*/

#pragma once
#ifndef AD2EASY_H
#define AD2EASY_H

#include <string>
#include <Windows.h>
#include <bitset>
#include <vector>
#include <sstream>
#include "dwf.h"

class AD2Easy
{
protected:
	HDWF hdwf;
public:
	// aux functions
	~AD2Easy();
	void init();
	void close();
	
	/////////////////////////////////////////////////////////////////////////////////////
	// bool/checker functions
	/////////////////////////////////////////////////////////////////////////////////////
	bool isConnected();									// check if an AD2 device is connected
	
	/////////////////////////////////////////////////////////////////////////////////////
	// set direction functions
	/////////////////////////////////////////////////////////////////////////////////////
	void setDir(int port, bool dir);					// set direction of specific port
	void setDirAll(bool dir);							// set direction of all ports, 0 - input, 1 - output

	/////////////////////////////////////////////////////////////////////////////////////
	// read functions
	/////////////////////////////////////////////////////////////////////////////////////
	bool read(int port);								// read data from specific port
	unsigned int read(std::string ports);				// read data from specific ports
	unsigned int readAll();								// read data from all active ports
	unsigned int readDirAll();

	/////////////////////////////////////////////////////////////////////////////////////
	// write functions
	/////////////////////////////////////////////////////////////////////////////////////									
	void write(int port, bool state);					// write data to specific port
	void write(std::string ports, unsigned int cmd);	// write data to specific ports
	void writeAll(unsigned int cmd);					// write data to all active ports

	/////////////////////////////////////////////////////////////////////////////////////
	// aux functions
	/////////////////////////////////////////////////////////////////////////////////////	
	void strToArr(std::string ports, std::vector<int>& x);
};

#endif // AD2EASY_H

