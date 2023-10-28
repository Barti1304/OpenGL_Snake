#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

class Renderer final
{
public:
	Renderer(int windowWidth, int windowHeight, const char* windowTitle);
	~Renderer();

	void initWindow(int width, int height, const char* title);
	void initShader();
	void initVAO();

	void renderSquare(int x, int y, int mapWidth, int mapHeight, const float* color) const;

	GLFWwindow* getWindow() { return window; }

private:
	void initRenderer();

	unsigned int vao, vbo;
	GLFWwindow* window;
	Shader* shader;
};