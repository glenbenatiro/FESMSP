#include "Window.h"

void Window::setTitle(std::string title)
{
	char temp[128];
	sprintf_s(temp, "title %s", title.c_str());
	system(temp);
}

void Window::setColor(std::string color)
{
	char temp[128];
	sprintf_s(temp, "color %s", color.c_str());
	system(temp);
}
