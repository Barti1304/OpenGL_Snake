#pragma once

class GameObject
{
public:
	GameObject(float* color);

	virtual void update() = 0;
	float* getCellColor();

private:
	float* cellColor;
};