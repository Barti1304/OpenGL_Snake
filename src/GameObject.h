#pragma once

constexpr float COLOR_GRAY[3]{ 0.25f, 0.25f, 0.25f };
constexpr float COLOR_BLUE[3]{ 0.0f, 0.5f, 1.0f };

class GameObject
{
public:
	virtual const float* getCellColor() = 0;
};