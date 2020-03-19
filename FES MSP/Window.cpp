#include "Window.h"

void Window::setTitle(std::string title)
{
	char temp[100];
	sprintf_s(temp, "title %s", title.c_str());
	system(temp);
}
