#pragma once

#include <GLFW/glfw3.h>

#include <iostream>
#include <algorithm>
#include <list>

class KeyboardManager final
{
public:
	void captureKeyboardInput(GLFWwindow* window);
	
	int getKeyboardInput();

private:
	int key;
};