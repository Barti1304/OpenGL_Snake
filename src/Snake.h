#pragma once

#include "GameObject.h"
#include "Renderer.h"
#include "KeyboardManager.h"
#include "SnakeBody.h"

#include <list>

class Snake final : public GameObject
{
public:
	Snake(int x, int y, float spd);

	void update() override;

	void render() override;


	void processKeyboardInput();


	int getSnakeX();
	int getSnakeY();

	static void setKeyboardManager(KeyboardManager* keyman);

private:
	void move();

	static KeyboardManager* keyboardManager;

	char direction;
	float speed;
	int size;

	std::list<SnakeBody*> body;
};