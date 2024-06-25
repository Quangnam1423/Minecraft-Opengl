#include "shader.h"



shader::shader(std::string _vertex, std::string _fragment)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;


	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vertexShaderFile.open(_vertex);
		fragmentShaderFile.open(_fragment);

		std::stringstream fragmentStream, vertexStream;

		vertexStream << vertexShaderFile.rdbuf();
		fragmentStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();

	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE__SUCCESSFULLY_READ: " << e.what() << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");



	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");


	// create shaderProgram in gpu and bind vertexShader and fragmentShader into shaderProgram
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");


	//delete vertexShader and fragmentShader in GPU's memory after bind successfully
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}
// ------------------------------------------------------------------------
void shader::use()
{
	glUseProgram(ID);
}

// ------------------------------------------------------------------------
//check the status when link or compile the shader program

void shader::checkCompileErrors(GLuint shader, std::string type)
{
	int success;
	char infoLog[512];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << std::endl;
		}
	}
}
// ------------------------------------------------------------------------
GLuint shader::getID()
{
	return ID;
}

// ------------------------------------------------------------------------
shader::~shader()
{
	glDeleteProgram(ID);
}
// ------------------------------------------------------------------------
void shader::setInt(const std::string& name, int value)
{
	use();
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void shader::setBool(const std::string& name, bool value)
{
	use();
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void shader::setFloat(const std::string& name, float value)
{
	use();
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void shader::setVec2(const std::string& name, const glm::vec2& value)
{
	use();
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
// ------------------------------------------------------------------------
void shader::setVec2(const std::string& name, float x, float y)
{
	use();
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void shader::setVec3(const std::string& name, const glm::vec3& value)
{
	use();
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void shader::setVec3(const std::string& name, float x, float y, float z)
{
	use();
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void shader::setVec4(const std::string& name, const glm::vec4& value)
{
	use();
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void shader::setVec4(const std::string& name, float x, float y, float z, float w)
{
	use();
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void shader::setMat2(const std::string& name, const glm::mat2& mat)
{
	use();
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void shader::setMat3(const std::string& name, const glm::mat3& mat)
{
	use();
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void shader::setMat4(const std::string& name, const glm::mat4& mat)
{
	use();
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
