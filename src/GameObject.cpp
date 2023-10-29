#include "GameObject.h"

Renderer* GameObject::renderer = nullptr;

GameObject::GameObject(int x, int y)
{
	xPos = x;
	yPos = y;
}

int GameObject::getXPos()
{
    return xPos;
}

int GameObject::getYPos()
{
	return yPos;
}

void GameObject::setGameObjectRenderer(Renderer* rnd)
{
	renderer = rnd;
}