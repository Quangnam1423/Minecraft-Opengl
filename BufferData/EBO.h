#pragma once
#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

class EBO
{
public:
	GLuint ID;
	EBO(std::vector<GLuint>& indices);
	~EBO();
	void Bind();
	void Unbind();
	void Delete();
};


#endif

