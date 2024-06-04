#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class GLFW_window
{
public:
	GLFW_window(int HEIGHT, int _WIDTH);
	~GLFW_window();
	void run();

private:
	unsigned int SCR_WIDTH;
	unsigned int SCR_HEIGHT;
	GLFWwindow* window;
};

