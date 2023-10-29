#pragma once

#include "GameObject.h"
#include "Renderer.h"
#include "SnakeBody.h"

#include <list>

class Snake final : public GameObject
{
public:
	Snake(int x, int y, float spd);

	void update(char keyboardInput);

	void render() override;

	int getSnakeX();
	int getSnakeY();

private:
	void move();

	char direction;
	float speed;
	int size;

	std::list<SnakeBody*> body;
};