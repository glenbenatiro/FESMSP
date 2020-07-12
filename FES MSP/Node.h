#pragma once
#ifndef NODE_H
#define NODE_H


#include "config.h"

class Node {
private:
	double vBend{ 0 };
	double vFlat{ 0 };
	double vRest{ 0 };
	double vFlex{ 0 };
	unsigned int posCMD = 0x000;
	unsigned int negCMD = 0x000;
	friend class Matrix;

	bool positiveEnabled = false;
	bool negativeEnabled = false;

public:
	bool isActive = false;

	void enablePositivePolarity(AD2Easy& ad2);
	void enableNegativePolarity(AD2Easy& ad2);
};

#endif // NODE_H

