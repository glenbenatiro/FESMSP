#pragma once
#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <conio.h>
#include <string>
#include "Matrix.h"

#include "Window.h"

class Session
{
private:
	// an object representation of the electrode matrix
	Matrix matrix;
	
public:
	// session constructor
	Session();

	int FES();
};

#endif 

