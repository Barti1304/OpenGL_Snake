#include "Game.h"

Game::Game(int windowWidth, int windowHeight, const char* windowTitle, int mapWidth, int mapHeight)
{
	renderer = new Renderer(windowWidth, windowHeight, windowTitle);

	this->initMap(mapWidth, mapHeight);
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

void Game::initMap(int width, int height)
{
	map = new Map(width, height);
}

void Game::update()
{
	glfwPollEvents();
}

void Game::render() const
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	map->renderMap(renderer);
	

	glfwSwapBuffers(renderer->getWindow());
}