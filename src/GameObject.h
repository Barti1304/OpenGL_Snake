#pragma once

constexpr float COLOR_GRAY[3]{ 0.25f, 0.25f, 0.25f };
constexpr float COLOR_BLUE[3]{ 0.0f, 0.5f, 1.0f };

#include "Renderer.h"

class GameObject
{
public:
	GameObject(int x, int y);

	virtual void render() = 0;
	virtual void update() {}

	int getXPos();
	int getYPos();

	static void setGameObjectRenderer(Renderer* rnd);

protected:
	static Renderer* renderer;
	int xPos, yPos;
};