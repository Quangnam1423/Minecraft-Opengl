#include "EBO.h"

EBO::EBO(std::vector<GLuint>& indices)
{
	glGenBuffers(GL_ELEMENT_ARRAY_BUFFER , &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0] , GL_STATIC_DRAW);
	Unbind();
}

EBO::~EBO()
{
	glDeleteBuffers(1, &ID);
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &ID);
}