#pragma once

#ifndef BLOCK_CLASS_H
#define BLOCK_CLASS_H

#include <glm/glm.hpp>

#include "Grass.h"
#include "cube.h"

enum class Type
{
	AIR,
	GRASS,
	STONE,
	WATER
};

struct Block
{
	Cube* thiscube;
	bool visible;
	glm::vec3 position;
	enum Type type;
};


#endif