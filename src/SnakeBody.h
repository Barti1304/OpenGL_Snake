#pragma once

#include "GameObject.h"

class SnakeBody final : public GameObject
{
public:
	SnakeBody(int x, int y);

	void render() override;
	
	void update() override;

	static void setSnakeSpeed(float speed);

private:
	float spawnTime;
	bool activeHitbox;

	static float snakeSpeed;
};