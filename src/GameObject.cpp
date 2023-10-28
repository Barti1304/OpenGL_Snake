#include "GameObject.h"

void GameObject::setCellColor(const float* color)
{
	cellColor = color;
}

const float* GameObject::getCellColor()
{
	return cellColor;
}