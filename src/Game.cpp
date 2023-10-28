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

	this->renderSquare(0, 0, COLOR_GRAY);
	
	glfwSwapBuffers(window);
}

void Game::renderSquare(int x, int y, const float color[3]) const
{
	float xPos = -1 + (float(x) / mapWidth);
	float yPos = 1 - (float(y) / mapHeight);
	float width = (float(1) / mapHeight) * 2;
	float height = (float(1) / mapWidth) * 2;

	float coords[]
	{
		xPos, yPos,							color[0], color[1], color[2],
		xPos, yPos - height,				color[0], color[1], color[2],
		xPos + width, yPos - height,		color[0], color[1], color[2],
		xPos, yPos,							color[0], color[1], color[2],
		xPos + width, yPos,					color[0], color[1], color[2],
		xPos + width, yPos - height,		color[0], color[1], color[2]
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_DYNAMIC_DRAW);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}