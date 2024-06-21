#pragma once

#ifndef VBO_CLASS_H
#define VBO_CLASS_H


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 Color;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
	int BoneIDs[4];
	float Weights[4];
};


class VBO
{
public:
	GLuint ID;
	VBO(std::vector<Vertex>& vertices);

	~VBO()
	{
		glDeleteBuffers(1 , &ID);
	}
	void Bind() const;
	void Unbind() const;
	void Delete() const;
};

#endif

