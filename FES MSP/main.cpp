#include <iostream>
#include "Session.h"
#include "UI.h"

int main()
{
	// instatiate session object and run its constructor
	Session session;

	// instantiate UI object
	UI ui;

	switch (ui.mainMenu().y) {
	case 0:
		break;
	case 1:
		exit(0);
		break;
	}

	return 0;
}