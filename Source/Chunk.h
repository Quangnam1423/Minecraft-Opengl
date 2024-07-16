#pragma once
#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <FastNoiseLite.h>

#include <vector>
#include <string>
#include <unordered_map>

#include "FastNoiseLite.h"
#include "ChunkMesh.h"
#include "Block.h"
#include "../Resource/Shader/shader.h"	
#include "World.h"
#include "Offset.h"


#define CHUNK_SIZE 32
#define CHUNK_HEIGHT 128
#define CHUNK_AREA 1024

class World;
class ChunkMesh;

class Chunk
{
public:
	Chunk(struct offset _offset, bool _visible , World* _world);
	void Draw(shader& ourShader);
	std::vector<Block*> blocks;
	World* m_world;
	offset get_offset()
	{
		return m_offset;
	}
	void build_chunkmesh();
private:
	
	void chunk_init(FastNoiseLite& noise2D , FastNoiseLite& noise3D);
	ChunkMesh *m_mesh;
	struct offset m_offset;
	bool visible;
};


#endif