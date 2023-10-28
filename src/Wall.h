#pragma once

#include "GameObject.h"

class Wall : public GameObject
{
public:
	const float* getCellColor() override;
};