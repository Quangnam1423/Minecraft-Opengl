#pragma once
#ifndef GRASS_CLASS_H
#define GRASS_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Resource/Shader/shader.h"
#include "cube.h"
#include <iostream>


class Grass : public Cube
{
public:
	Grass(glm::vec3 _position) : Cube(_position)
	{	
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// note that VAO is in use
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		//set attribute for the vertex attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
		//unbind the buffer and vertex array when load status and vertice sucessfullly
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	};

	void Draw(shader& ourShader) override;

	~Grass()
	{

	}

private:
	unsigned int VAO, VBO, EBO;
	float vertices[288] = {
		// front face
		// positions          // colors           // texture coords
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.5f , 0.75f,   // bottom left
		0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   0.75f , 0.75f,   // bottom right
		0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.75f , 0.99f,   // top right
		0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.75f , 0.99f,   // top right
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.5f , 0.99f,    // top left 
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.5f , 0.75f,   // bottom left

		//behind face
		// positions          // colors           // texture coords
		0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.5f , 0.75f,   // bottom left
		-0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   0.75f , 0.75f,   // bottom right
		-0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.75f , 0.99f,   // top right
		-0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.75f , 0.99f,   // top right
		0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 0.0f,    0.5f , 0.99f,    // top left 
		0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,	  0.5f,  0.75f, // bottom left

		//right face
		// positions          // colors           // texture coords
		0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.5f , 0.75f,   // bottom left
		0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   0.75f , 0.75f,   // bottom right
		0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.75f , 0.99f,   // top right
		0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.75f , 0.99f,   // top right
		0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.5f , 0.99f,    // top left 
		0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.5f , 0.75f,   // bottom left

		//left face
		// positions          // colors           // texture coords
		-0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.5f , 0.75f,   // bottom left
		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   0.75f , 0.75f,   // bottom right
		-0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.75f , 0.99f,   // top right
		-0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.75f , 0.99f,   // top right
		-0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 0.0f,   0.5f , 0.99f,    // top left 
		-0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.5f , 0.75f,   // bottom left

		//top face
		// positions          // colors           // texture coords
		-0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.75f , 0.5f,   // bottom left
		0.5f, 0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.5f,   // bottom right
		0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 0.75f,   // top right
		0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 0.75f,   // top right
		-0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 0.0f,   0.75f , 0.75f,    // top left 
		-0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.75f , 0.5f,   // bottom left

		//bottom face
		// positions          // colors           // texture coords
		-0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.25f , 0.75f,   // bottom left
		0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   0.5f , 0.75f,   // bottom right
		0.5f,  -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.5f , 1.0f,   // top right
		0.5f,  -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.5f , 1.0f,   // top right
		-0.5f,  -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.25f , 1.0f,    // top left 
		-0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.25f , 0.75f,   // bottom left
	};

	GLuint indices[36]  = {
		0 , 1 , 2 ,		3 , 4 , 5 , //front face
		6 , 7 , 8 ,		9 , 10 , 11 ,  //right face
		12, 13, 14,		15, 16, 17 ,  //bihind face
		18, 19, 20,		21, 22, 23 , //left face
		24, 25, 26,		27, 28, 29 ,//top face
		30, 31, 32,		33, 34, 35//bottom face
	};
};

#endif