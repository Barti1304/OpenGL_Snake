#include "Map.h"

Map::Map(int width, int height)
{
	mapWidth = width;
	mapHeight = height;

	map.resize(width * height);

	const int* mapCode = new int[mapWidth * mapHeight];

	for (int i = 0; i < mapWidth; i++)
	{
		map[i] = new Wall(i, 0);
		map[i + (mapHeight - 1) * mapWidth] = new Wall(i, mapHeight - 1);
		map[i * mapWidth] = new Wall(0, i);
		map[i * mapWidth + mapHeight - 1] = new Wall(mapWidth - 1, i);
	}
}

void Map::renderMap() const
{
	for (auto obj : map)
		if (obj != nullptr)
			obj->render();
}

bool Map::checkCollisionsWithSnake(Snake* snake)
{
	for (auto wall : map)
		if (wall && wall->getXPos() == snake->getXPos() && wall->getYPos() == snake->getYPos())
			return true;

	return false;
}

GameObject* Map::operator[](int index)
{
	return map[index];
}