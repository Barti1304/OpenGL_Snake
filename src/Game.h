#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <windows.h>

class Game final
{
public:
	Game(int width, int height, const char* title);
	~Game();

	void run();

private:
	void update();
	void render() const;

	GLFWwindow* window;
};