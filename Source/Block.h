#pragma once

#ifndef BLOCK_CLASS_H
#define BLOCK_CLASS_H

#include <glm/glm.hpp>
#include "../Resource/Shader/shader.h"

// position of each vertex of cube 
#define BLOCK_LEFT_TOPLEFT(x, y, z)			glm::vec3(-0.5f + x, 0.5f  + y, -0.5f + z)
#define BLOCK_LEFT_BOTTOMLEFT(x, y, z)		glm::vec3(-0.5f + x, -0.5f + y, -0.5f + z)
#define BLOCK_LEFT_BOTTOMRIGHT(x, y, z) 	glm::vec3(-0.5f + x, -0.5f + y, 0.5f  + z)
#define BLOCK_LEFT_TOPRIGHT(x, y, z) 		glm::vec3(-0.5f + x, 0.5f  + y, 0.5f  + z)

#define BLOCK_RIGHT_TOPLEFT(x, y, z)		glm::vec3(0.5f + x, 0.5f  + y, 0.5f  + z)
#define BLOCK_RIGHT_BOTTOMLEFT(x, y, z)		glm::vec3(0.5f + x, -0.5f + y, 0.5f  + z)
#define BLOCK_RIGHT_BOTTOMRIGHT(x, y, z) 	glm::vec3(0.5f + x, -0.5f + y, -0.5f + z)
#define BLOCK_RIGHT_TOPRIGHT(x, y, z) 		glm::vec3(0.5f + x, 0.5f  + y, -0.5f + z)

#define BLOCK_TOP_TOPLEFT(x, y, z)			glm::vec3(-0.5f + x, 0.5f + y, -0.5f + z)
#define BLOCK_TOP_BOTTOMLEFT(x, y, z)		glm::vec3(-0.5f + x, 0.5f + y, 0.5f  + z)
#define BLOCK_TOP_BOTTOMRIGHT(x, y, z) 		glm::vec3(0.5f  + x, 0.5f + y, 0.5f  + z)
#define BLOCK_TOP_TOPRIGHT(x, y, z) 		glm::vec3(0.5f  + x, 0.5f + y, -0.5f + z)

#define BLOCK_BOTTOM_TOPLEFT(x, y, z)		glm::vec3(-0.5f + x, -0.5f + y, 0.5f  + z)
#define BLOCK_BOTTOM_BOTTOMLEFT(x, y, z)	glm::vec3(-0.5f + x, -0.5f + y, -0.5f + z)
#define BLOCK_BOTTOM_BOTTOMRIGHT(x, y, z) 	glm::vec3(0.5f  + x, -0.5f + y, -0.5f + z)
#define BLOCK_BOTTOM_TOPRIGHT(x, y, z) 		glm::vec3(0.5f  + x, -0.5f + y, 0.5f  + z)

#define BLOCK_FRONT_TOPLEFT(x, y, z)		glm::vec3(-0.5f + x, 0.5f  + y, 0.5f + z)
#define BLOCK_FRONT_BOTTOMLEFT(x, y, z)		glm::vec3(-0.5f + x, -0.5f + y, 0.5f + z)
#define BLOCK_FRONT_BOTTOMRIGHT(x, y, z) 	glm::vec3(0.5f  + x, -0.5f + y, 0.5f + z)
#define BLOCK_FRONT_TOPRIGHT(x, y, z) 		glm::vec3(0.5f  + x, 0.5f  + y, 0.5f + z)

#define BLOCK_BACK_TOPLEFT(x, y, z)			glm::vec3(0.5f  + x, 0.5f  + y, -0.5f + z)
#define BLOCK_BACK_BOTTOMLEFT(x, y, z)		glm::vec3(0.5f  + x, -0.5f + y, -0.5f + z)
#define BLOCK_BACK_BOTTOMRIGHT(x, y, z) 	glm::vec3(-0.5f + x, -0.5f + y, -0.5f + z)
#define BLOCK_BACK_TOPRIGHT(x, y, z) 		glm::vec3(-0.5f + x, 0.5f  + y, -0.5f + z)

//Textcoords of the texture
#define TEXTCOORD_BOTTOMLEFT(x , y) glm::vec2(x + 0.0f, y + 0.0f)
#define TEXTCOORD_BOTTOMRIGHT(x , y) glm::vex2(x + 0.333f , y + 0.0f)
#define TEXTCOORD_TOPLEFT(x , y) glm::vec2(x + 0.0f , y + 0.333f)
#define TEXTCOORD_TOPRIGHT(x , y) glm::vec2(x + 0.333f , y + 0.333f)

//Grass alas coords
#define GRASS_TOP_ALAS glm::vec2(0.75f , 0.5f)
#define GRASS_SIDE_ALAS glm::vec2(0.5f , 0.75f)
#define GRASS_BOTTOM_ALAS glm::vec2(0.25f , 0.75f)
//Sand alas coords
#define SAND_ALAS glm::vec2(0.25f , 0.75f)



// Block face normals
#define BLOCK_NORMAL_LEFT 	-1.0f, 0.0f, 0.0f
#define BLOCK_NORMAL_RIGHT 	1.0f, 0.0f, 0.0f
#define BLOCK_NORMAL_TOP 	0.0f, 1.0f, 0.0f
#define BLOCK_NORMAL_BOTTOM 0.0f, -1.0f, 0.0f
#define BLOCK_NORMAL_FRONT 	0.0f, 0.0f, 1.0f
#define BLOCK_NORMAL_BACK 	0.0f, 0.0f, -1.0f


//Type of block 
enum class Type
{
	AIR,
	GRASS,
	STONE,
	WATER,
	SAND
};

//face of cube
enum class Face
{
	FRONT,
	RIGHT,
	BACK,
	LEFT,
	TOP,
	BOTTOM
};

//Define Vertex attributes
struct Vertex
{
	glm::vec3 position;
	glm::vec2 textCoords;
	int id;
};

class Block
{
public:
	Block(enum Type _type, glm::vec3 _position, unsigned int _id)
	{
		type = _type;
		position = _position;
		id = _id;
	}

	~Block() {};

	Type get_type()
	{
		return type;
	}

	glm::vec3 get_position()
	{
		return position;
	}

	unsigned int get_id()
	{
		return id;
	}
	//front face
	std::vector<Vertex> get_front_face()
	{
		std::vector<Vertex> ans;
		//first triangle
		Vertex bottom_left;
		bottom_left.position = BLOCK_FRONT_BOTTOMLEFT(position.x, position.y, position.z);
		bottom_left.textCoords = glm::vec2(0.0f, 0.0f);
		bottom_left.id = id;
		ans.push_back(bottom_left);
		Vertex bottom_right;
		bottom_right.position = BLOCK_FRONT_BOTTOMRIGHT(position.x, position.y, position.z);
		bottom_right.textCoords = glm::vec2(0.0f, 0.0f);
		bottom_right.id = id;
		ans.push_back(bottom_right);
		Vertex top_right;
		top_right.position = BLOCK_FRONT_TOPRIGHT(position.x, position.y, position.z);
		top_right.textCoords = glm::vec2(0.0f, 0.0f);
		top_right.id = id;
		ans.push_back(top_right);
		
		//second triangle
		ans.push_back(top_right);
		Vertex top_left;
		top_left.position = BLOCK_FRONT_TOPLEFT(position.x, position.y, position.z);
		top_left.textCoords = glm::vec2(0.0f, 0.0f);
		top_left.id = id;
		ans.push_back(top_left);

		ans.push_back(bottom_left);
		return ans;
	}

	//back face
	std::vector<Vertex> get_back_face()
	{
		std::vector<Vertex> ans;
		//first triangle
		Vertex bottom_left;
		bottom_left.position = BLOCK_BACK_BOTTOMLEFT(position.x, position.y, position.z);
		bottom_left.textCoords = glm::vec2(0.0f, 0.0f);
		bottom_left.id = id;
		ans.push_back(bottom_left);
		Vertex bottom_right;
		bottom_right.position = BLOCK_BACK_BOTTOMRIGHT(position.x, position.y, position.z);
		bottom_right.textCoords = glm::vec2(0.0f, 0.0f);
		bottom_right.id = id;
		ans.push_back(bottom_right);
		Vertex top_right;
		top_right.position = BLOCK_BACK_TOPRIGHT(position.x, position.y, position.z);
		top_right.textCoords = glm::vec2(0.0f, 0.0f);
		top_right.id = id;
		ans.push_back(top_right);

		//second triangle
		ans.push_back(top_right);
		Vertex top_left;
		top_left.position = BLOCK_BACK_TOPLEFT(position.x, position.y, position.z);
		top_left.textCoords = glm::vec2(0.0f, 0.0f);
		top_left.id = id;
		ans.push_back(top_left);

		ans.push_back(bottom_left);
		return ans;
	}
	// right face
	std::vector<Vertex> get_right_face()
	{
		std::vector<Vertex> ans;
		//first triangle
		Vertex bottom_left;
		bottom_left.position = BLOCK_RIGHT_BOTTOMLEFT(position.x, position.y, position.z);
		bottom_left.textCoords = glm::vec2(0.0f, 0.0f);
		bottom_left.id = id;
		ans.push_back(bottom_left);
		Vertex bottom_right;
		bottom_right.position = BLOCK_RIGHT_BOTTOMRIGHT(position.x, position.y, position.z);
		bottom_right.textCoords = glm::vec2(0.0f, 0.0f);
		bottom_right.id = id;
		ans.push_back(bottom_right);
		Vertex top_right;
		top_right.position = BLOCK_RIGHT_TOPRIGHT(position.x, position.y, position.z);
		top_right.textCoords = glm::vec2(0.0f, 0.0f);
		top_right.id = id;
		ans.push_back(top_right);

		//second triangle
		ans.push_back(top_right);
		Vertex top_left;
		top_left.position = BLOCK_RIGHT_TOPLEFT(position.x, position.y, position.z);
		top_left.textCoords = glm::vec2(0.0f, 0.0f);
		top_left.id = id;
		ans.push_back(top_left);

		ans.push_back(bottom_left);
		return ans;
	}
	//left face
	std::vector<Vertex> get_left_face()
	{
		std::vector<Vertex> ans;
		//first triangle
		Vertex bottom_left;
		bottom_left.position = BLOCK_LEFT_BOTTOMLEFT(position.x, position.y, position.z);
		bottom_left.textCoords = glm::vec2(0.0f, 0.0f);
		bottom_left.id = id;
		ans.push_back(bottom_left);
		Vertex bottom_right;
		bottom_right.position = BLOCK_LEFT_BOTTOMRIGHT(position.x, position.y, position.z);
		bottom_right.textCoords = glm::vec2(0.0f, 0.0f);
		bottom_right.id = id;
		ans.push_back(bottom_right);
		Vertex top_right;
		top_right.position = BLOCK_LEFT_TOPRIGHT(position.x, position.y, position.z);
		top_right.textCoords = glm::vec2(0.0f, 0.0f);
		top_right.id = id;
		ans.push_back(top_right);

		//second triangle
		ans.push_back(top_right);
		Vertex top_left;
		top_left.position = BLOCK_LEFT_TOPLEFT(position.x, position.y, position.z);
		top_left.textCoords = glm::vec2(0.0f, 0.0f);
		top_left.id = id;
		ans.push_back(top_left);

		ans.push_back(bottom_left);
		return ans;
	}
	// top face
	std::vector<Vertex> get_top_face()
	{
		std::vector<Vertex> ans;
		//first triangle
		Vertex bottom_left;
		bottom_left.position = BLOCK_TOP_BOTTOMLEFT(position.x, position.y, position.z);
		bottom_left.textCoords = glm::vec2(0.0f, 0.0f);
		bottom_left.id = id;
		ans.push_back(bottom_left);
		Vertex bottom_right;
		bottom_right.position = BLOCK_TOP_BOTTOMRIGHT(position.x, position.y, position.z);
		bottom_right.textCoords = glm::vec2(0.0f, 0.0f);
		bottom_right.id = id;
		ans.push_back(bottom_right);
		Vertex top_right;
		top_right.position = BLOCK_TOP_TOPRIGHT(position.x, position.y, position.z);
		top_right.textCoords = glm::vec2(0.0f, 0.0f);
		top_right.id = id;
		ans.push_back(top_right);

		//second triangle
		ans.push_back(top_right);
		Vertex top_left;
		top_left.position = BLOCK_TOP_TOPLEFT(position.x, position.y, position.z);
		top_left.textCoords = glm::vec2(0.0f, 0.0f);
		top_left.id = id;
		ans.push_back(top_left);

		ans.push_back(bottom_left);
		return ans;
	}
	// bottom face
	std::vector<Vertex> get_bottom_face()
	{
		std::vector<Vertex> ans;
		//first triangle
		Vertex bottom_left;
		bottom_left.position = BLOCK_BOTTOM_BOTTOMLEFT(position.x, position.y, position.z);
		bottom_left.textCoords = glm::vec2(0.0f, 0.0f);
		bottom_left.id = id;
		ans.push_back(bottom_left);
		Vertex bottom_right;
		bottom_right.position = BLOCK_BOTTOM_BOTTOMRIGHT(position.x, position.y, position.z);
		bottom_right.textCoords = glm::vec2(0.0f, 0.0f);
		bottom_right.id = id;
		ans.push_back(bottom_right);
		Vertex top_right;
		top_right.position = BLOCK_BOTTOM_TOPRIGHT(position.x, position.y, position.z);
		top_right.textCoords = glm::vec2(0.0f, 0.0f);
		top_right.id = id;
		ans.push_back(top_right);

		//second triangle
		ans.push_back(top_right);
		Vertex top_left;
		top_left.position = BLOCK_BOTTOM_TOPLEFT(position.x, position.y, position.z);
		top_left.textCoords = glm::vec2(0.0f, 0.0f);
		top_left.id = id;
		ans.push_back(top_left);

		ans.push_back(bottom_left);
		return ans;
	}

private:
	enum Type type;
	glm::vec3 position;
	unsigned int id;
};

class Cube
{
public:
	Cube()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textCoords));
		glEnableVertexAttribArray(2);
		glVertexAttribIPointer(2, 1, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, id));
		glBindVertexArray(0);
	}
	void Draw(shader& ourShader)
	{
		ourShader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	GLuint VAO, VBO, EBO;
	std::vector<Vertex> vertices = {
		// front face
		// positions          // colors           // texture coords
		Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.5f , 0.75f), 1} , // bottom left
		Vertex{glm::vec3(0.5f, -0.5f, -0.5f),glm::vec2(0.75f , 0.75f) , 1},   // bottom right
		Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(0.75f , 0.99f),1} ,   // top right
		Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(0.75f , 0.99f),1} ,  // top right
		Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.5f , 0.99f),1} ,   // top left 
		Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.5f , 0.75f),1} ,  // bottom left

		//behind face
		// positions          // colors           // texture coords
		Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(0.5f , 0.75f),1} ,  // bottom left
		Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.75f , 0.75f), 1} , // bottom right
		Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec2(0.75f , 0.99f), 1} , // top right
		Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec2(0.75f , 0.99f), 1} , // top right
		Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec2(0.5f , 0.99f), 1}  , // top left 
		Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(0.5f,  0.75f), 1} , // bottom left

		//right face
		// positions          // colors           // texture coords
		Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.5f , 0.75f),1} ,   // bottom left
		Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(0.75f , 0.75f),1 } ,   // bottom right
		Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec2(0.75f , 0.99f),1 },   // top right
		Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec2(0.75f , 0.99f), 1},   // top right
		Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(0.5f , 0.99f),1} ,    // top left 
		Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.5f , 0.75f), 1} ,   // bottom left

		//left face
		// positions          // colors           // texture coords
		Vertex{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.5f , 0.75f),1} ,   // bottom left
		Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.75f , 0.75f), 1} ,   // bottom right
		Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.75f , 0.99f), 1},   // top right
		Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.75f , 0.99f), 1} ,   // top right
		Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec2(0.5f , 0.99f),1},    // top left 
		Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.5f , 0.75f), 1},   // bottom left

		//top face
		// positions          // colors           // texture coords
		Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.75f , 0.5f), 1},   // bottom left
		Vertex{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 0.5f),1},   // bottom right
		Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec2(1.0f, 0.75f),1},   // top right
		Vertex{glm::vec3(0.5f , 0.5f ,0.5f) , glm::vec2(1.0f , 0.75f) , 1},   // top right
		Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec2(0.75f , 0.75f),1} ,    // top left 
		Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.75f , 0.5f),1},   // bottom left

		//bottom face
		// positions          // colors           // texture coords
		Vertex{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.25f , 0.75f),1} ,   // bottom left
		Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(0.5f , 0.75f),1} ,   // bottom right
		Vertex{glm::vec3(0.5f,  -0.5f, -0.5f), glm::vec2(0.5f , 1.0f), 1} ,   // top right
		Vertex{glm::vec3(0.5f,  -0.5f, -0.5f), glm::vec2(0.5f , 1.0f), 1} ,   // top right
		Vertex{glm::vec3(-0.5f,  -0.5f, -0.5f), glm::vec2(0.25f , 1.0f),1} ,    // top left 
		Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.25f , 0.75f), 1}   // bottom left
	};

	std::vector<GLuint> indices = {
		0 , 1 , 2 ,		3 , 4 , 5 , //front face
		6 , 7 , 8 ,		9 , 10 , 11 ,  //right face
		12, 13, 14,		15, 16, 17 ,  //bihind face
		18, 19, 20,		21, 22, 23 , //left face
		24, 25, 26,		27, 28, 29 ,//top face
		30, 31, 32,		33, 34, 35//bottom face
	};
};


#endif