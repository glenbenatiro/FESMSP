#pragma once
#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <Windows.h>

class Navigator
{
public:
	int x = 0;
	int y = 0;
	int xAbs = 0;
	int yAbs = 0;

	static void gotoxy(int x, int y);
};

#endif NAVIGATOR_H

