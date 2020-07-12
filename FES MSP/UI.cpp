#include "UI.h"
#include <iostream>

Navigator UI::navigator(int xInit, int yInit, int xStep, int yStep, int xMax, int yMax)
{
	// init vars
	int x{ xInit };
	int y{ yInit };
	int choice;

	Navigator coord;

	if (!xStep)
		xStep = 1;
	if (!yStep)
		yStep = 1;

	// draw initial 'x' mark
	coord.gotoxy(x, y);
	std::cout << "x";

	while (1) {
		if (choice = _getch()) {
			// remove 'x' mark from current position
			coord.gotoxy(x, y);
			std::cout << " ";

			switch (choice) {
			case ev::keymap::up:
				y = (y - yStep < yInit) ? yMax : y - yStep;
				break;
			case ev::keymap::down:
				y = (y + yStep > yMax) ? yInit : y + yStep;
				break;
			case ev::keymap::left:
				x = (x - xStep < xInit) ? xMax : x - xStep;
				break;
			case ev::keymap::right:
				x = (x + xStep > xMax) ? xInit : x + xStep;
			case ev::keymap::enter:
				coord.xAbs = x;
				coord.yAbs = y;

				for (int xCount = xInit; xCount < x; xCount += xStep) {
					++coord.x;
				}
				for (int yCount = yInit; yCount < y; yCount += yStep) {
					++coord.y;
				}

				return coord;
				break;
			default:
				break;
			}

			// write 'x' mark in new position
			coord.gotoxy(x, y);
			std::cout << "x";
		}
	}
}



Navigator UI::mainMenu()
{
	Navigator::gotoxy(0, 0); std::cout << "[ ] Begin stimulation";
	Navigator::gotoxy(0, 1); std::cout << "[ ] Exit";

	return this->navigator(1, 0, 0, 1, 1, 0);
}
