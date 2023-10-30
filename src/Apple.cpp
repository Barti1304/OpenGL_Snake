#include "Apple.h"

Apple::Apple() : GameObject(0, 0) {}

void Apple::render()
{
	renderer->renderSquare(xPos, yPos, COLOR_RED);
}

void Apple::goToRandomPosition(int mapWidth, int mapHeight)
{
	std::random_device rdX;
	std::random_device rdY;
	std::uniform_int_distribution<int> distX(1, mapWidth - 2);
	std::uniform_int_distribution<int> distY(1, mapHeight - 2);

	xPos = distX(rdX);
	yPos = distY(rdY);
}