#pragma once
#ifndef AD2_H
#define AD2_H

#include <Windows.h>
#include "AD2Easy.h"
#include "dwf.h"
#include "env_vars.h"
using namespace ev;

class AD2 : public AD2Easy {
private:
public:
	~AD2();
	void init();
	void writeDIO(unsigned short int cmd);
	double readAIO(int channel);
	void writeSPI(unsigned char* cmd);
};

#endif // AD2_H