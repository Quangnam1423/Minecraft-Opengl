#pragma once

#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include "EBO.h"
#include "VBO.h"

class VAO
{
public:
	GLuint ID;
	EBO* ebo;
	VBO* vbo;
	VAO(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
	~VAO();
	void Bind();
	void Unbind();
	void Delete();
	void linkAttrib();
};

#endif

