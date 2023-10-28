#include "Map.h"

Map::Map(int width, int height)
{
	mapWidth = width;
	mapHeight = height;

	map.resize(width * height);

	const int* mapCode = new int[mapWidth * mapHeight];

	for (int i = 0; i < mapWidth; i++)
	{
		map[i] = new Wall;
		map[i + (mapHeight - 1) * mapWidth] = new Wall;
		map[i * mapWidth] = new Wall;
		map[i * mapWidth + mapHeight - 1] = new Wall;
	}
}

void Map::renderMap(Renderer* renderer) const
{
	for (int i = 0; i < mapWidth * mapHeight; i++)
		if (map[i] != nullptr)
			renderer->renderSquare((i % mapWidth), (i / mapWidth), mapWidth, mapHeight, map[i]->getCellColor());
}

GameObject* Map::operator[](int index)
{
	return map[index];
}