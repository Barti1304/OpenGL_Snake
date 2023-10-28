#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <windows.h>

#include "Renderer.h"
#include "Wall.h"
#include "Map.h"

class Game final
{
public:
	Game(int windowWidth, int windowHeight, const char* windowTitle, int mapWidth, int mapHeight);
	~Game();

	void run();

private:
	void initMap(int width, int height);

	void update();
	void render() const;

	Renderer* renderer;
	Map* map;
};