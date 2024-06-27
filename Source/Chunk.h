#pragma once
#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <string>
#include <unordered_map>

#include "ChunkMesh.h"
#include "Block.h"
#include "../Resource/Shader/shader.h"


#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 16
#define CHUNK_AREA 256


struct offset {
	int x;
	int y;
};

class Chunk
{
public:
	Chunk(struct offset _offset, bool _visible);
	void Draw(shader& ourShader);
	std::vector<Block*> blocks;
private:
	void chunk_init();
	ChunkMesh *m_mesh;
	struct offset m_offset;
	bool visible;
};


#endif