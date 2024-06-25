#pragma once

#ifndef CUBE_CLASS_H
#define CUBE_CLASS_H
#include <glm/glm.hpp>

class Cube
{
public:
	virtual ~Cube()
	{
		if (VAO)
		{
			glDeleteVertexArrays(1, &VAO);
		}
		if (VBO)
		{
			glDeleteBuffers(1, &VBO);
		}
		if (EBO)
		{
			glDeleteBuffers(1, &EBO);
		}
	};

	Cube(glm::vec3 _position) : position(_position)
	{

	};
	virtual void  Draw(shader &outShader)
	{

	};
	glm::vec3 position;
	unsigned int VAO, VBO, EBO;
};

#endif