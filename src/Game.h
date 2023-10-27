#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <windows.h>

#include "Shader.h"

class Game final
{
public:
	Game(int width, int height, const char* title);
	~Game();

	void run();

private:
	void initOpenGL(int width, int height, const char* title);
	void initVAO();


	void update();


	void render() const;


	unsigned int vao, vbo;
	GLFWwindow* window;
	Shader* shader;
};