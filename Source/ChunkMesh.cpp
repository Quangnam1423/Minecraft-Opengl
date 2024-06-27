#include "ChunkMesh.h"

ChunkMesh::ChunkMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	vertices.clear();
	indices.clear();
}

ChunkMesh::~ChunkMesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void ChunkMesh::addAttribute()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textCoords));
	glEnableVertexAttribArray(2);
	glVertexAttribIPointer(2, 1, GL_INT , sizeof(Vertex), (void*)offsetof(Vertex, id));
	glBindVertexArray(0);
}

void ChunkMesh::add_vertex(Vertex _vertex)
{
	vertices.push_back(_vertex);
	indices.push_back(indices.size());
}

void ChunkMesh::add_vertices(std::vector<Vertex> _vertices)
{
	for (int i = 0 ; i < _vertices.size() ; i++)
	{
		vertices.push_back(_vertices[i]);
		indices.push_back(indices.size());
	}
	return;
}

void ChunkMesh::Draw(shader& ourShader)
{
	ourShader.use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}