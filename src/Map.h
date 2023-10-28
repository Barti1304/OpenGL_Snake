#pragma once

#include <glad/glad.h>

#include <vector>

#include "GameObject.h"
#include "Renderer.h"

#include "Wall.h"

class Map
{
public:
	Map(int width, int height);

	void renderMap(Renderer* renderer) const;
	
	GameObject* operator[](int index);

private:
	int mapWidth, mapHeight;
	std::vector<GameObject*> map;
};