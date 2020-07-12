#pragma once
#ifndef AD2_FESMSP_H
#define AD2_FESMSP_H

#include "AD2_Easy.h"
#include "Windows.h"
#include "config.h"

class AD2_FESMSP : public AD2Easy
{
private:
	double hzSys = 0;
public:
	void rampPotentiometer(float seconds, unsigned char* direction);
	void init();
};

#endif // AD2_FESMSP_H
