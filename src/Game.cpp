#include "Game.h"

#define DISABLE_CONFIG

Game::Game(int windowWidth, int windowHeight, const char* windowTitle, int mapWidth, int mapHeight)
{
#ifndef DISABLE_CONFIG
	this->gameConfig();
#endif

	keyboardManager = new KeyboardManager;

	renderer = new Renderer(windowWidth, windowHeight, windowTitle, mapWidth, mapHeight);
	GameObject::setGameObjectRenderer(renderer);

	snake = new Snake(mapWidth * 0.5f, mapHeight * 0.5f, 5);
	Snake::setKeyboardManager(keyboardManager);

	map = new Map(mapWidth, mapHeight);
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
	renderer->updateTitleBar(snake->getScore());

	// keyboard input
	glfwPollEvents();
	keyboardManager->captureKeyboardInput(renderer->getWindow());
	this->processKeyboardInput(keyboardManager);


	// update snake and its body
	snake->update();

	// check collisions
	if (map->checkCollisionsWithSnake(snake))
		this->gameOver();
	
	if (snake->checkCollisionsWithBody())
		this->gameOver();
}

void Game::render() const
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	snake->render();
	map->renderMap();
	

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

void Game::gameConfig()
{

}

void Game::gameOver()
{
	glfwSetWindowShouldClose(renderer->getWindow(), true);

	std::cout << "Game over!\n"
		<< "Your score is " << snake->getScore() << '\n';

	if (snake->getScore() > 125)
		std::cout << "You're killing it!!! B-)\n";
	else if (snake->getScore() > 60)
		std::cout << "Wonderful! ^u^";
	else if (snake->getScore() > 35)
		std::cout << "Awesome! :D";
	else if (snake->getScore() > 20)
		std::cout << "Pretty good :)";
	else if (snake->getScore() > 10)
		std::cout << "Okay :|";
	else
		std::cout << "Too bad :(";
	std::cout << "\n\n";
}