#pragma once

#include "GameObject.h"

#include <random>

class Apple : public GameObject
{
public:
	Apple();

	void render() override;

	void goToRandomPosition(int mapWidth, int mapHeight);
};