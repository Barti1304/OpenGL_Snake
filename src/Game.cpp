#include "Game.h"

Game::Game(int windowWidth, int windowHeight, const char* windowTitle, int mapWidth, int mapHeight)
{
	renderer = new Renderer(windowWidth, windowHeight, windowTitle, mapWidth, mapHeight);
	GameObject::setGameObjectRenderer(renderer);

	map = new Map(mapWidth, mapHeight);
	
	snake = new Snake(mapWidth * 0.5f, mapHeight * 0.5f, 3);


	keyboardInput = 'd';
}

Game::~Game()
{
	glfwTerminate();
}

void Game::run()
{
	while (!glfwWindowShouldClose(renderer->getWindow()))
	{
		this->update();
		this->render();

		Sleep(1000 / 120);
	}
}

void Game::update()
{
	glfwPollEvents();

	this->processInput();

	snake->update(keyboardInput);
}

void Game::render() const
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	map->renderMap();
	snake->render();
	

	glfwSwapBuffers(renderer->getWindow());
}

void Game::processInput()
{
	if (glfwGetKey(renderer->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(renderer->getWindow(), true);

	if (glfwGetKey(renderer->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
		keyboardInput = 'w';
	if (glfwGetKey(renderer->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
		keyboardInput = 'a';
	if (glfwGetKey(renderer->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
		keyboardInput = 's';
	if (glfwGetKey(renderer->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
		keyboardInput = 'd';
}