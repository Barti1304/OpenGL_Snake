#pragma once

constexpr float COLOR_GRAY[3]{ 0.4f, 0.4f, 0.4f };
constexpr float COLOR_BLUE[3]{ 0.0f, 0.2f, 0.8f };

class GameObject
{
public:
	virtual const float* getCellColor() = 0;
};