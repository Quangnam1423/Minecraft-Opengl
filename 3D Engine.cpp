#include "Source/GLFW_window.h"

int main()
{
	Window* window = new Window(800, 800);
	window->run();

	return 0;
}