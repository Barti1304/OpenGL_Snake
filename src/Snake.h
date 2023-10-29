#pragma once

#include "GameObject.h"
#include "Renderer.h"

class Snake : public GameObject
{
public:
	Snake(int x, int y, float spd);

	void update(char keyboardInput);

	void render(Renderer* renderer);

	const float* getCellColor() override;

	int getSnakeX();
	int getSnakeY();

private:
	void move();

	int xPos, yPos;
	char direction;
	float speed;
};