#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "SingleTon.h"
#include "Resource/Shader/shader.h"
#include <stb_image.h>

class Window :public SingleTon
{
public:
	Window(int HEIGHT, int _WIDTH);
	Window() {};
	~Window();
	void run();

private:

	float vertices[32] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	unsigned int indices[6] = {
		0 , 1 , 3 , //first triangle
		1 , 2 , 3 // second triangle
	};

	unsigned int SCR_WIDTH;
	unsigned int SCR_HEIGHT;
	unsigned int VBO , VAO , EBO;
	shader* ourShader;

	GLFWwindow* window;
};

