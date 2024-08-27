#include "Chunk.h"

glm::vec3 get_position(int x, int y, int z , struct offset m_offset);
bool check_is_solid(glm::vec3 position , Chunk *_chunk);

Chunk::Chunk(struct offset _offset, bool _visible , World *_world) : m_world(_world)
{
	m_offset = _offset;
	visible = _visible;
	m_mesh = new ChunkMesh();
	blocks.resize(CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT, nullptr);
	chunk_init(m_world->noise2D , m_world->noise3D);
}
 
void Chunk::Draw(shader& ourShader)
{
	m_mesh->Draw(ourShader , m_offset);
}

void Chunk::chunk_init(FastNoiseLite& noise2D , FastNoiseLite& noise3D)
{
	for (int z = 0; z < CHUNK_SIZE; z++)
	{
		for (int x = 0; x < CHUNK_SIZE; x++)
		{
			float x_noise = static_cast<float>(m_offset.x * CHUNK_SIZE + x);
			float y_noise = static_cast<float>(m_offset.y * CHUNK_SIZE + z);
			int height_size = CHUNK_SIZE * noise2D.GetNoise(x_noise, y_noise) + CHUNK_HEIGHT / 2;

			for (int y = 0; y < height_size; y++)
			{
				unsigned int id = x + y + z;
				glm::vec3 position = get_position(x, y, z, this->m_offset);
				int block_id = x + z * CHUNK_SIZE + y * CHUNK_AREA;

				float noiseValue = noise3D.GetNoise(x_noise, (float)y, y_noise);
				noiseValue = (noiseValue + 1.0f) * 0.5f;
				if (noiseValue < 0.4f)
					continue;
				else if (noiseValue < 0.5f && y != height_size - 1)
				{
					blocks[block_id] = new Block(Type::SAND, position, id);
				}
				else if (noiseValue < 0.5f && y == height_size - 1)
				{
					blocks[block_id] = new Block(Type::GRASS, position, id);
				}
				else if (noiseValue < 0.56f)
				{
					if (y > CHUNK_HEIGHT / 2)
						blocks[block_id] = new Block(Type::SAND, position, id);
					else
						blocks[block_id] = new Block(Type::STONE, position, id);
				}
				else
					blocks[block_id] = new Block(Type::STONE, position, id);
			}
		}
	}
}

void Chunk::build_chunkmesh()
{
	// build chunk mesh 
	for (int z = 0; z < CHUNK_SIZE; z++)
	{
		for (int x = 0; x < CHUNK_SIZE; x++)
		{
			for (int y = 0; y < CHUNK_HEIGHT; y++)
			{
				unsigned int id = x + z * CHUNK_SIZE + y * CHUNK_AREA;
				if (blocks[id] == nullptr)
					continue;
				//top face
				if (!check_is_solid(glm::vec3(x, y + 1, z), this))
				{
					this->m_mesh->add_vertices(blocks[id]->get_top_face());
				}
				//front face
				if (!check_is_solid(glm::vec3(x, y, z + 1), this))
				{
					this->m_mesh->add_vertices(blocks[id]->get_front_face());
				}
				//right face
				if (!check_is_solid(glm::vec3(x + 1, y, z), this))
				{
					this->m_mesh->add_vertices(blocks[id]->get_right_face());
				}
				//back face
				if (!check_is_solid(glm::vec3(x, y, z - 1), this))
				{
					this->m_mesh->add_vertices(blocks[id]->get_back_face());
				}
				//left face
				if (!check_is_solid(glm::vec3(x - 1, y, z), this))
				{
					this->m_mesh->add_vertices(blocks[id]->get_left_face());
				}
				//bottom face
				if (!check_is_solid(glm::vec3(x, y - 1, z), this))
				{
					this->m_mesh->add_vertices(blocks[id]->get_bottom_face());
				}
			}
		}
	}
	m_mesh->addAttribute();
}

glm::vec3 get_position(int x, int y, int z, struct offset m_offset)
{
	return glm::vec3(0.5f + x, y + 0.5f,z - 0.5f);
}

bool check_is_solid(glm::vec3 position, Chunk* _chunk)
{
	// if the blocks is in bottom of the chunk return true for no display on screen
	if (position.y < 0)
		return true;
	// if the blocks is in top of the chunk return true for no display on screen 
	if (position.y >= CHUNK_HEIGHT)
		return false;

	offset next_offset = _chunk->get_offset();
	glm::vec3 next_position = position;
	if (position.x < 0)
	{
		next_offset.x -= 1;
		next_position.x = CHUNK_SIZE - 1;
	}
	if (position.x == CHUNK_SIZE)
	{
		next_offset.x += 1;
		next_position.x = 0;
	}
	if (position.z < 0)
	{
		next_offset.y -= 1;
		next_position.z = CHUNK_SIZE - 1;
	}
	if (position.z == CHUNK_SIZE)
	{
		next_offset.y += 1;
		next_position.z = 0;
	}
	if (next_offset == _chunk->get_offset())
	{
		int id = position.x + position.z * CHUNK_SIZE + position.y * CHUNK_AREA;
		if (_chunk->blocks[id] != nullptr && _chunk->blocks[id]->get_type() != Type::AIR)
			return true;
		return false;
	}
	else
	{
		World* _world = _chunk->m_world;
		if (_world->map.count(next_offset))
		{
			int id = next_position.x + next_position.z * CHUNK_SIZE + next_position.y * CHUNK_AREA;
			if (_world->map[next_offset]->blocks[id] == nullptr)
				return false;
			if (_world->map[next_offset]->blocks[id]->get_type() != Type::AIR)
				return true;
			return false;
		}
		return true;
	}
}