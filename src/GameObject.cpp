#include "GameObject.h"

GameObject::GameObject(float* color)
{
	cellColor = color;
}

float* GameObject::getCellColor()
{
	return cellColor;
}