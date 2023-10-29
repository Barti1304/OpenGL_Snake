#include "Snake.h"

Snake::Snake(int x, int y, float spd)
{
	xPos = x;
	yPos = y;
	speed = 1.0f / spd;

	direction = 'd';
}

void Snake::update(char keyboardInput)
{
	static float moveTime = speed;

	if (glfwGetTime() > moveTime)
	{
		this->move();

		moveTime += speed;
	}

	direction = keyboardInput;
}

void Snake::render(Renderer* renderer)
{
	renderer->renderSquare(xPos, yPos, COLOR_BLUE);
}

const float* Snake::getCellColor()
{
    return COLOR_BLUE;
}

int Snake::getSnakeX()
{
	return xPos;
}

int Snake::getSnakeY()
{
	return yPos;
}

void Snake::move()
{
	switch (direction)
	{
	case 'w':
		yPos -= 1;
		break;
	case 'a':
		xPos -= 1;
		break;
	case 's':
		yPos += 1;
		break;
	case 'd':
		xPos += 1;
		break;
	}
}