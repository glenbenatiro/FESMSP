#include "AD2.h"
#include "Matrix.h"
#include "UI.h"
#include "Window.h"

AD2 ad2;
Matrix matrix;
UI ui;

int main()
{
	// change cmd window title
	Window::setTitle("FES MSP");

	if (!ad2.isConnected()) {
		exit(0);
	}
	else {
		ad2.init();
	}

	// draw main menu UI
	ui.mainMenu();

	while (1) { 
		switch (ui.mainMenu().y) {
		case 0:
			// session();
			break;
		case 1:
			exit(0);
			break;
		default:
			break;
		}
	}

	return 0;
}