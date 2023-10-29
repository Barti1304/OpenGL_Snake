#include "SnakeBody.h"

float SnakeBody::snakeSpeed = 0.0f;

SnakeBody::SnakeBody(int x, int y) : GameObject(x, y)
{
	spawnTime = glfwGetTime();
	activeHitbox = false;
}

void SnakeBody::render()
{
	renderer->renderSquare(xPos, yPos, COLOR_BLUE);
}

void SnakeBody::update()
{
	if (glfwGetTime() > (spawnTime + snakeSpeed + 0.1f))
		activeHitbox = true;
}

void SnakeBody::setSnakeSpeed(float speed)
{
	snakeSpeed = speed;
}