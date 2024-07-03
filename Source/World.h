#pragma once

#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Chunk.h"
#include "Chunkmesh.h"
#include "../Resource/Shader/shader.h"

#include <iostream>
#include <unordered_map>
#include <iomanip>
#include <cstring>

class Chunk;

class World
{
public:
	World();
	~World();
	void Draw(shader& ourShader);std::unordered_map<offset, Chunk*> map;
	
	//void world_resize(glm::vec3 position);
private:
	void world_init();
	
};

#endif