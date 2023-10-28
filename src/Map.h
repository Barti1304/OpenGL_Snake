#pragma once

#include <glad/glad.h>

#include <vector>

#include "GameObject.h"
#include "Wall.h"

class Map
{
public:
	Map(int width, int height);


	void updateMap();


	void renderMap() const;
	void renderSquare(int x, int y, const float* color) const;


	void setMapObject(int x, int y, GameObject* obj);
	
private:
	int mapWidth, mapHeight;
	std::vector<GameObject*> map;
};