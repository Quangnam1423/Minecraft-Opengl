#pragma once

#include "glad/glad.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

class shader
{

public:
	void setBool(const std::string& name, bool value);

    void setInt(const std::string& name, int value);

	void setFloat(const std::string& name, float value);
	shader() {};
	shader(std::string vertex, std::string fragment);
	~shader();
	void use();
	GLuint getID();
private:
	GLuint ID;

	void checkCompileErrors(GLuint shader, std::string type);

};

