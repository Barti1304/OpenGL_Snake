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

	map = new Map(mapWidth, mapHeight);

	snake = new Snake(mapWidth * 0.5f, mapHeight * 0.5f, 5);
	Snake::setKeyboardManager(keyboardManager);

	apple = new Apple;
	apple->goToRandomPosition(map->getWidth(), map->getHeight());
}

void Game::run()
{
	while (!glfwWindowShouldClose(renderer->getWindow()))
	{
		this->update();
		this->render();

		Sleep(1000 / 120);
	}

	glfwTerminate();
	this->printPostGameInfo();
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
	if (snake->checkCollisions(map->getMapContainer()))
		this->gameOver();

	if (snake->checkCollisions(snake->getBodyContainer()))
		this->gameOver();

	// scoring system
	if (snake->checkCollisions(apple->getXPos(), apple->getYPos()))
	{
		snake->addPoint();

		while (this->isAppleTouchingSnake())
			apple->goToRandomPosition(map->getWidth(), map->getHeight());
	}
}

void Game::render() const
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	apple->render();
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
}

void Game::printPostGameInfo()
{
	std::cout << "Game over!\n"
		<< "Your score is " << snake->getScore() << '\n';

	float mapPercentage = (snake->getLenght() * 100.0f) / (map->getWidth() * map->getHeight());
	std::cout << "You've covered " << std::setprecision(3) << mapPercentage << "% of the " <<
		map->getWidth() << 'x' << map->getHeight() << " map!\n";

	if (mapPercentage >= 75)
		std::cout << "You're killing it!!! ^u^\n";
	else if (mapPercentage >= 55)
		std::cout << "Wonderful! :3";
	else if (mapPercentage >= 30)
		std::cout << "Awesome! :D";
	else if (mapPercentage >= 15)
		std::cout << "Pretty good :)";
	else if (mapPercentage >= 5)
		std::cout << "Okay :|";
	else
		std::cout << "Too bad :(";
	std::cout << "\n\n";

	system("pause");
}

bool Game::isAppleTouchingSnake()
{
	for (auto bodyPart : snake->getBodyContainer())
		if (bodyPart->getXPos() == apple->getXPos() && bodyPart->getYPos() == apple->getYPos())
			return true;

	if (snake->getXPos() == apple->getXPos() && snake->getYPos() == apple->getYPos())
		return true;

	return false;
}