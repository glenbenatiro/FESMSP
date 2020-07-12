#pragma once
#ifndef UI_H
#define UI_h

#include <conio.h>
#include "Navigator.h"
#include "config.h"

class UI {
private:
public:
	Navigator navigator(int xInit, int yInit, int xStep, int yStep, int xMax, int yMax);
	Navigator mainMenu();
};

#endif // UI_H

