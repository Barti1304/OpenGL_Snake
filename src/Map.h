#pragma once

#include <glad/glad.h>

#include <vector>

#include "GameObject.h"
#include "Renderer.h"

#include "Snake.h"
#include "Wall.h"

class Map final
{
public:
	Map(int width, int height);

	void renderMap() const;


	int getWidth();
	int getHeight();

	std::vector<GameObject*> getMapContainer();
	
	GameObject* operator[](int index);

private:
	int mapWidth, mapHeight;
	std::vector<GameObject*> map;
};