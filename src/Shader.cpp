#include "Shader.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	std::fstream vRead(vertexShaderPath);
	std::fstream fRead(fragmentShaderPath);

	std::stringstream vStr;
	std::stringstream fStr;

	vStr << vRead.rdbuf();
	fStr << fRead.rdbuf();

	std::string vString = vStr.str();
	std::string fString = fStr.str();

	const char* vSourceCode = vString.c_str();
	const char* fSourceCode = fString.c_str();
	
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vSourceCode, 0);
	glCompileShader(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fSourceCode, 0);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use() const
{
	glUseProgram(shaderProgram);
}

unsigned int Shader::id() const
{
	return shaderProgram;
}
