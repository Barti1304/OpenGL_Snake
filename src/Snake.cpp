#include "Snake.h"

KeyboardManager* Snake::keyboardManager = nullptr;

Snake::Snake(int x, int y, float spd) : GameObject(x, y)
{
	SnakeBody::setSnakeSpeed(spd);

	direction = 'D';
	speed = 1.0f / spd;
	size = 5;
}

void Snake::update()
{
	static float moveTime = speed;
	if (glfwGetTime() > moveTime)
	{
		body.push_back(new SnakeBody(xPos, yPos));

		this->processKeyboardInput();
		this->move();

		moveTime += speed;
	}


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

bool Snake::checkCollisions(std::vector<GameObject*> container)
{
	for (auto obj : container)
		if (obj && obj->getXPos() == this->getXPos() && obj->getYPos() == this->getYPos())
			return true;

	return false;
}

bool Snake::checkCollisions(std::list<SnakeBody*> container)
{
	for (auto obj : container)
		if (obj && obj->getXPos() == this->getXPos() && obj->getYPos() == this->getYPos())
			return true;

	return false;
}

bool Snake::checkCollisions(int x, int y)
{
	if (this->getXPos() == x && this->getYPos() == y)
		return true;

	return false;
}

void Snake::processKeyboardInput()
{
	switch (keyboardManager->getKeyboardInput())
	{
	case GLFW_KEY_W:
		if (direction != 'S')
			direction = 'W';
			break;

	case GLFW_KEY_A:
		if (direction != 'D')
			direction = 'A';
			break;

	case GLFW_KEY_S:
		if (direction != 'W')
			direction = 'S';
			break;

	case GLFW_KEY_D:
		if (direction != 'A')
			direction = 'D';
			break;
	}
}

void Snake::setKeyboardManager(KeyboardManager* keyman)
{
	keyboardManager = keyman;
}

int Snake::getScore()
{
	return size - 5;
}

int Snake::getLenght()
{
	return size;
}

void Snake::addPoint()
{
	size++;
}

std::list<SnakeBody*> Snake::getBodyContainer()
{
	return body;
}

void Snake::move()
{
	switch (direction)
	{
	case 'W':
		yPos -= 1;
		break;
	case 'A':
		xPos -= 1;
		break;
	case 'S':
		yPos += 1;
		break;
	case 'D':
		xPos += 1;
		break;
	}
}