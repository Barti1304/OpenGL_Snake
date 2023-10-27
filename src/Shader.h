#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

	void use() const;
	unsigned int id() const;

private:
	unsigned int shaderProgram;
};