#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "SingleTon.h"
#include "Resource/Shader/shader.h"


class Window :public SingleTon
{
public:
	Window() {};
	Window(int HEIGHT, int _WIDTH);
	~Window();
	void run();
	bool loadTexture(std::string name);

private:

	float vertices[288] = {
		// front face
		// positions          // colors           // texture coords
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,    // top left 
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left

		//behind face
		// positions          // colors           // texture coords
		0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		-0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,    // top left 
		0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left

		//right face
		// positions          // colors           // texture coords
		0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,    // top left 
		0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left

		//left face
		// positions          // colors           // texture coords
		-0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		-0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		-0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,    // top left 
		-0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left

		//top face
		// positions          // colors           // texture coords
		-0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		0.5f, 0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		-0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,    // top left 
		-0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left

		//bottom face
		// positions          // colors           // texture coords
		-0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		0.5f,  -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		0.5f,  -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		-0.5f,  -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,    // top left 
		-0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	};

	unsigned int indices[36] = {
		0 , 1 , 2 ,		3 , 4 , 5 , //front face
		6 , 7 , 8 ,		9 , 10 , 11 ,  //right face
		12, 13, 14,		15, 16, 17 ,  //bihind face
		18, 19, 20,		21, 22, 23 , //left face
		24, 25, 26,		27, 28, 29 ,//top face
		30, 31, 32,		33, 34, 35//bottom face
	};

	unsigned int SCR_WIDTH;
	unsigned int SCR_HEIGHT;
	unsigned int VBO , VAO , EBO;
	shader* ourShader;

	GLFWwindow* window;
};



	