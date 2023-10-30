#pragma once

#include "GameObject.h"
#include "Renderer.h"
#include "KeyboardManager.h"
#include "SnakeBody.h"
#include "Map.h"

#include <list>

class Snake final : public GameObject
{
public:
	Snake(int x, int y, float spd);

	void update() override;

	void render() override;


	bool checkCollisions(std::vector<GameObject*> container);
	bool checkCollisions(std::list<SnakeBody*> container);
	bool checkCollisions(int x, int y);

	void processKeyboardInput();
	
	static void setKeyboardManager(KeyboardManager* keyman);

	int getScore();
	int getLenght();

	void addPoint();

	std::list<SnakeBody*> getBodyContainer();

private:
	void move();

	static KeyboardManager* keyboardManager;

	char direction;
	float speed;
	int size;

	std::list<SnakeBody*> body;
};