#pragma once
#ifndef CHUNK_MESH_CLASS_H
#define CHUNK_MESH_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <FastNoiseLite.h>

#include <vector>
#include <iostream>

#include "Block.h"
#include "Offset.h"
#include "Chunk.h"
#include "../Resource/Shader/shader.h"

class ChunkMesh
{
public:
	ChunkMesh();

	~ChunkMesh();

	void add_vertex(Vertex _vertex);
	void add_vertices(std::vector<Vertex> _vertices);

	void addAttribute();
	void Draw(shader& ourShader , struct offset _offset);
private:
	GLuint VAO, VBO, EBO;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
};

#endif