#include "Game.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Game::Game(int windowWidth, int windowHeight, const char* windowTitle, int mapW, int mapH)
{
	mapWidth = mapW;
	mapHeight = mapH;

	this->initOpenGL(windowWidth, windowHeight, windowTitle);
	this->initVAO();
	this->initMap();

	shader = new Shader("./src/shader.vert", "./src/shader.frag");
}

Game::~Game()
{
	glfwTerminate();
}

void Game::run()
{
	while (!glfwWindowShouldClose(window))
	{
		this->update();
		this->render();

		Sleep(1000 / 120);
	}
}

void Game::initOpenGL(int width, int height, const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	window = glfwCreateWindow(width, height, title, 0, 0);

	if (!window)
		exit(-1);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		exit(-1);
}

void Game::initVAO()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Game::initMap()
{
	map = new Map(mapWidth, mapHeight);

	const int* mapCode = new int[mapWidth * mapHeight];
	for (int i = 0; i < mapWidth; i++)
	{
		map->setMapObject(i, 0, new Wall);
		map->setMapObject(i, mapHeight - 1, new Wall);
		map->setMapObject(0, i, new Wall);
		map->setMapObject(mapWidth - 1, i, new Wall);
	}
}

void Game::update()
{
	glfwPollEvents();
}

void Game::render() const
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader->use();
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	map->renderMap();
	
	glfwSwapBuffers(window);
}