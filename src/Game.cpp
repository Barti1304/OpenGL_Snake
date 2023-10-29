#include "Game.h"

Game::Game(int windowWidth, int windowHeight, const char* windowTitle, int mapWidth, int mapHeight)
{
	keyboardManager = new KeyboardManager;

	renderer = new Renderer(windowWidth, windowHeight, windowTitle, mapWidth, mapHeight);
	GameObject::setGameObjectRenderer(renderer);

	map = new Map(mapWidth, mapHeight);
	
	snake = new Snake(mapWidth * 0.5f, mapHeight * 0.5f, 5);
	Snake::setKeyboardManager(keyboardManager);
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
	// keyboard input
	glfwPollEvents();
	keyboardManager->captureKeyboardInput(renderer->getWindow());
	this->processKeyboardInput(keyboardManager);


	// update snake and its body
	snake->update();
}

void Game::render() const
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	map->renderMap();
	snake->render();
	

	glfwSwapBuffers(renderer->getWindow());
}

void Game::processKeyboardInput(KeyboardManager* keyman)
{
	switch (keyman->getKeyboardInput())
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(renderer->getWindow(), true);
		break;
	}
}