#pragma once

#include "glad/glad.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

class shader
{

public:
    void setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
	shader() {};
	shader(std::string vertex, std::string fragment);
	~shader();
	void use();
private:
	GLuint ID;

	void checkCompileErrors(GLuint shader, std::string type);

};

