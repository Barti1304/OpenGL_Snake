#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

class Renderer final
{
public:
	Renderer(int windowWidth, int windowHeight, const char* windowTitle, int mapW, int mapH);
	~Renderer();

	void renderSquare(int x, int y, const float* color) const;

	GLFWwindow* getWindow();

private:
	void initWindow(int width, int height, const char* title);
	void initShader();
	void initVAO();

	int mapWidth, mapHeight;

	unsigned int vao, vbo;
	GLFWwindow* window;
	Shader* shader;
};