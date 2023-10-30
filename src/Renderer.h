#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

class Renderer final
{
public:
	Renderer(int windowWidth, int windowHeight, const char* windowTitle, int mapW, int mapH, int dims);
	~Renderer();

	void renderSquare(int x, int y, const float* color) const;

	GLFWwindow* getWindow();

	void updateTitleBar(int src);

private:
	void initWindow(int width, int height, const char* title);
	void initShader();
	void initVAO();

	int dimensions;

	int mapWidth, mapHeight;

	unsigned int vao, vbo, ebo;
	unsigned int texture;

	GLFWwindow* window;
	Shader* shader;
};