#include "World.h"
#include <cstdlib>


World::World()
{
	noise2D.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	Seed = rand() % INT_MAX;
	noise2D.SetFrequency(0.015);
	noise2D.SetSeed(Seed);
	
	noise3D.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	noise3D.SetFrequency(0.2f);
	noise3D.SetSeed(Seed);

	world_init();
}

World::~World()
{
	for (auto& entry : map)
	{
		delete entry.second;
	}
	map.clear();
}

void World::world_init()
{
	int view_limit = static_cast<int>(80 / CHUNK_SIZE);
	for (int i = -view_limit; i <= view_limit; i++)
		for (int j = -view_limit; j <= view_limit; j++)
			map[offset{ i , j }] = new Chunk(offset{ i , j }, true , this);
	for (auto& entry : map)
	{
		entry.second->build_chunkmesh();
	}
}

void World::Draw(shader &ourShader)
{
	ourShader.use();
	for (const auto& entry : map)
	{
		entry.second->Draw(ourShader);
	}
}