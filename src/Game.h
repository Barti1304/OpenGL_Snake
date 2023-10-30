#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <windows.h>
#include <iomanip>

#include "KeyboardManager.h"
#include "Renderer.h"
#include "Map.h"
#include "Wall.h"
#include "Snake.h"
#include "Apple.h"

class Game final
{
public:
	Game(int windowWidth, int windowHeight, const char* windowTitle, int mapWidth, int mapHeight, int dimensions);

	void run();

private:
	void update();
	void render() const;

	void processKeyboardInput(KeyboardManager* keyman);

	void gameConfig();
	void gameOver();
	void printPostGameInfo();

	bool isAppleTouchingSnake();

	KeyboardManager* keyboardManager;
	Renderer* renderer;
	Map* map;

	Snake* snake;
	Apple* apple;
};