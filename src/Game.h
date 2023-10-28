#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <windows.h>

#include "Shader.h"

constexpr float COLOR_GRAY[3]{ 0.4f, 0.4f, 0.4f };

class Game final
{
public:
	Game(int windowWidth, int windowHeight, const char* windowTitle, int mapW, int mapH);
	~Game();

	void run();

private:
	void initOpenGL(int width, int height, const char* title);
	void initVAO();


	void update();


	void render() const;
	void renderSquare(int x, int y, const float color[3]) const;


	unsigned int vao, vbo;

	int mapWidth, mapHeight;

	GLFWwindow* window;
	Shader* shader;
};