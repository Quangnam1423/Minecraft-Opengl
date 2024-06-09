#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "SingleTon.h"

class Window :public SingleTon
{
public:
	Window(int HEIGHT, int _WIDTH);
	~Window();
	void run();

private:

	float vertices[18] = {
		//first triangle
		-0.5f , -0.5f , 0.0f , //top right
		0.5f , -0.5f , 0.0f , //bottom right
		0.0f , 0.5f , 0.0f , //top left

		//second triangle
		0.6f , 0.6f , 0.0f , //bottom right
		1.0f , 1.0f , 0.0f , // bottom left
		1.0f , 0.0f , 0.0f  // top left
	};

	unsigned int indices[9] = {
		0 , 1 , 2 ,// first triangle
		3 , 4 , 5 // second triangle

		, 1 , 2 , 3
	};

	unsigned int SCR_WIDTH;
	unsigned int SCR_HEIGHT;
	unsigned int VBO , VAO , EBO;
	unsigned int vertexShader , fragmentShader , shaderProgram;


	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	GLFWwindow* window;
};

