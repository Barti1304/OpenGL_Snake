#include "Snake.h"

Snake::Snake(int x, int y, float spd) : GameObject(x, y)
{
	SnakeBody::setSnakeSpeed(spd);

	direction = 'd';
	speed = 1.0f / spd;
	size = 8;
}

void Snake::update(char keyboardInput)
{
	static float moveTime = speed;

	if (glfwGetTime() > moveTime)
	{
		body.push_back(new SnakeBody(xPos, yPos));

		this->move();

		moveTime += speed;
	}

	direction = keyboardInput;

	while (body.size() > size)
		body.pop_front();

	for (auto it = body.begin(); it != body.end(); it++)
		(*it)->update();
}

void Snake::render()
{
	for (auto it = body.begin(); it != body.end(); it++)
		(*it)->render();

	renderer->renderSquare(xPos, yPos, COLOR_BLUE);
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