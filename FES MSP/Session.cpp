#include "Session.h"

Session::Session()
{
	// change console window title and color
	Window::setTitle("FES MSP v1.0");
	Window::setColor("f0");

	// get tuple output from isConnected function
	std::tuple returnValue = matrix.ad2.isConnected();

	// display error and exit if AD2 is not connected
	if (!std::get<0>(returnValue)) {
		std::cout << "Analog Discovery 2 is not connected." << "\n";
		std::cout << std::get<1>(returnValue) << "\n";
		std::cout << "Press any key to exit.";
		_getch();
		exit(0);
	}
	else {
		// initialize all necessary settings on AD2 for the program
		matrix.ad2.init();
	}
}

int Session::FES()
{
	// gather initial data to get flex bending percentage per node, and to determine target electrode
	matrix.gatherInitialData();

	return 0;
}