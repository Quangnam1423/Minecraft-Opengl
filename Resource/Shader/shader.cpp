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

void shader::use()
{
	glUseProgram(ID);
}


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

GLuint shader::getID()
{
	return ID;
}


shader::~shader()
{
	glDeleteProgram(ID);
}

void shader::setInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void shader::setBool(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void shader::setFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}