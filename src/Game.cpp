#include "Game.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Game::Game(int width, int height, const char* title)
{
	this->initOpenGL(width, height, title);
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
	const float coords[]
	{
		-0.5f, -0.5f,		1, 0, 0,
		0.5f, -0.5f,		0, 1, 0,
		-0.5f, 0.5f,		0, 0, 1
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_DYNAMIC_DRAW);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Game::update()
{
	glfwPollEvents();



	Sleep(1000 / 120);
}

void Game::render() const
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader->use();

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glfwSwapBuffers(window);
}