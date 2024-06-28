#include "Chunk.h"

glm::vec3 get_position(int x, int y, int z , struct offset m_offset);
bool check_is_solid(glm::vec3 position , std::vector<Block*> &block);

Chunk::Chunk(struct offset _offset, bool _visible)
{
	m_offset = _offset;
	visible = _visible;
	m_mesh = new ChunkMesh();
	//blocks.resize(CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT);
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

	// build chunk mesh 
	for (int z = 0; z < CHUNK_SIZE; z++)
	{
		for (int x = 0; x < CHUNK_SIZE; x++)
		{
			for (int y = 0; y < CHUNK_HEIGHT; y++)
			{
				unsigned int id = x + z * CHUNK_SIZE + y * CHUNK_AREA;
				//top face
				if (!check_is_solid(glm::vec3(x, y + 1, z) , blocks))
				{
					this->m_mesh->add_vertices(blocks[id]->get_top_face());
				}
				//front face
				if (!check_is_solid(glm::vec3(x, y, z + 1) , blocks))
				{
					this->m_mesh->add_vertices(blocks[id]->get_front_face());
				}
				//right face
				if (!check_is_solid(glm::vec3(x + 1, y, z) , blocks))
				{
					this->m_mesh->add_vertices(blocks[id]->get_right_face());
				}
				//back face
				if (!check_is_solid(glm::vec3(x, y, z - 1) , blocks))
				{
					this->m_mesh->add_vertices(blocks[id]->get_back_face());
				}
				//left face
				if (!check_is_solid(glm::vec3(x - 1, y, z) , blocks))
				{
					this->m_mesh->add_vertices(blocks[id]->get_left_face());
				}
				//bottom face
				if (!check_is_solid(glm::vec3(x , y - 1, z) , blocks))
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

bool check_is_solid(glm::vec3 position, std::vector<Block*>& blocks)
{
	if (position.x < 0 || position.x >= CHUNK_SIZE || position.z < 0 || position.z >= CHUNK_SIZE || position.y < 0 || position.y >= CHUNK_HEIGHT)
		return false;
	int id = position.x + position.z * CHUNK_SIZE + position.y * CHUNK_AREA;
	if (blocks[id]->get_type() == Type::GRASS)
		return true;
	return false;
}