#include "KeyboardManager.h"

void KeyboardManager::captureKeyboardInput(GLFWwindow* window)
{
	for (int c = 32; c < 348; c++)
		if (glfwGetKey(window, c) == GLFW_PRESS)
			key = c;
}

int KeyboardManager::getKeyboardInput()
{
	return key;
}