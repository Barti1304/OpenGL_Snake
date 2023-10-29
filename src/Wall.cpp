#include "Wall.h"

Wall::Wall(int x, int y) : GameObject(x, y) {}

void Wall::render()
{
	renderer->renderSquare(xPos, yPos, COLOR_GRAY);
}