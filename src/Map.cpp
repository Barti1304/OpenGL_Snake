#include "Map.h"

Map::Map(int width, int height)
{
	mapWidth = width;
	mapHeight = height;

	map.resize(width * height);
}

void Map::updateMap()
{

}

void Map::renderMap() const
{
	for (int i = 0; i < mapWidth * mapHeight; i++)
		if (map[i] != nullptr)
			this->renderSquare((i % mapWidth), (i / mapWidth), map[i]->getCellColor());
}

void Map::renderSquare(int x, int y, const float* color) const
{
	float xPos = -1 + (float(x) / mapWidth) * 2;
	float yPos = 1 - (float(y) / mapHeight) * 2;
	float width = (float(1) / mapHeight) * 2;
	float height = (float(1) / mapWidth) * 2;

	float coords[]
	{
		xPos, yPos,							color[0], color[1], color[2],
		xPos, yPos - height,				color[0], color[1], color[2],
		xPos + width, yPos - height,		color[0], color[1], color[2],
		xPos, yPos,							color[0], color[1], color[2],
		xPos + width, yPos,					color[0], color[1], color[2],
		xPos + width, yPos - height,		color[0], color[1], color[2]
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_DYNAMIC_DRAW);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Map::setMapObject(int x, int y, GameObject* obj)
{
	map[x + mapWidth * y] = obj;
}