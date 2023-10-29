#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <windows.h>
#include <iomanip>

#include "KeyboardManager.h"
#include "Renderer.h"
#include "Map.h"
#include "Snake.h"
#include "Wall.h"

class Game final
{
public:
	Game(int windowWidth, int windowHeight, const char* windowTitle, int mapWidth, int mapHeight);
	~Game();

	void run();

private:
	void update();
	void render() const;

	void processKeyboardInput(KeyboardManager* keyman);

	void gameConfig();
	void gameOver();

	KeyboardManager* keyboardManager;
	Renderer* renderer;
	Snake* snake;
	Map* map;
};