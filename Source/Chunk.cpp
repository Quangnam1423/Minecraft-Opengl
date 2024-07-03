#include "Chunk.h"

glm::vec3 get_position(int x, int y, int z , struct offset m_offset);
bool check_is_solid(glm::vec3 position , Chunk *_chunk);

Chunk::Chunk(struct offset _offset, bool _visible , World *_world) : m_world(_world)
{
	m_offset = _offset;
	visible = _visible;
	m_mesh = new ChunkMesh();
	chunk_init();
}
 
void Chunk::Draw(shader& ourShader)
{
	m_mesh->Draw(ourShader , m_offset);
}

void Chunk::chunk_init()
{
	int count = 0;
	for (int y = 0; y < CHUNK_HEIGHT; y++)
	{
		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			for (int x = 0; x < CHUNK_SIZE; x++)
			{
				unsigned int id = x + y + z;
				glm::vec3 position = get_position(x, y, z , this->m_offset);
				Block* new_block = new Block(Type::GRASS , position , id);
				blocks.push_back(new_block);
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
		if (_chunk->blocks[id]->get_type() == Type::GRASS)
			return true;
		return false;
	}
	else
	{
		World* _world = _chunk->m_world;
		if (_world->map.count(next_offset))
		{
			int id = next_position.x + next_position.z * CHUNK_SIZE + next_position.y * CHUNK_AREA;
			if (_world->map[next_offset]->blocks[id]->get_type() == Type::GRASS)
				return true;
			return false;
		}
	}
}