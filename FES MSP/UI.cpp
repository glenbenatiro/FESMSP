#include "UI.h"
#include <iostream>

Navigator UI::navigator(int xInit, int yInit, int xStep, int yStep, int xMax, int yMax)
{
	// init vars
	int x{ xInit };
	int y{ yInit };
	int choice{};

	constexpr int KEY_UP = 72;
	constexpr int KEY_DOWN = 80;
	constexpr int KEY_LEFT = 75;
	constexpr int KEY_RIGHT = 77;
	constexpr int ENTER = 13;
	constexpr int BACKSPACE = 8;

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
			case KEY_UP:
				y = (y - yStep < yInit) ? yMax : y - yStep;
				break;
			case KEY_DOWN:
				y = (y + yStep > yMax) ? yInit : y + yStep;
				break;
			case KEY_LEFT:
				x = (x - xStep < xInit) ? xMax : x - xStep;
				break;
			case KEY_RIGHT:
				x = (x + xStep > xMax) ? xInit : x + xStep;
			case ENTER:
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
