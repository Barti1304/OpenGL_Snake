#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <windows.h>

#include "Shader.h"
#include "Map.h"

class Game final
{
public:
	Game(int windowWidth, int windowHeight, const char* windowTitle, int mapW, int mapH);
	~Game();

	void run();

private:
	void initOpenGL(int width, int height, const char* title);
	void initVAO();
	void initMap();


	void update();


	void render() const;


	unsigned int vao, vbo;

	int mapWidth, mapHeight;

	GLFWwindow* window;
	Shader* shader;
	Map* map;
};