#pragma once

constexpr float COLOR_GRAY[3]{ 0.4f, 0.4f, 0.4f };

class GameObject
{
public:
	const float* getCellColor();

protected:
	void setCellColor(const float* color);

private:
	const float* cellColor;
};