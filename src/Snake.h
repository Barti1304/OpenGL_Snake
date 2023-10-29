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


	bool checkCollisionsWithBody();

	void processKeyboardInput();
	
	static void setKeyboardManager(KeyboardManager* keyman);

	int getScore();

private:
	void move();

	static KeyboardManager* keyboardManager;

	char direction;
	float speed;
	int size;

	std::list<SnakeBody*> body;
};