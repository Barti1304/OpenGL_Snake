#include "Renderer.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Renderer::Renderer(int windowWidth, int windowHeight, const char* windowTitle, int mapW, int mapH)
{
	this->initWindow(windowWidth, windowHeight, windowTitle);
	this->initShader();
	this->initVAO();

	mapWidth = mapW;
	mapHeight = mapH;
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void Renderer::initWindow(int width, int height, const char* title)
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

void Renderer::initShader()
{
	shader = new Shader("./src/shader.vert", "./src/shader.frag");
	shader->use();
}

void Renderer::initVAO()
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

void Renderer::renderSquare(int x, int y, const float* color) const
{
	float xPos = -1 + (float(x) / mapWidth) * 2;
	float yPos = 1 - (float(y) / mapHeight) * 2;
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

	glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_DYNAMIC_DRAW);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

GLFWwindow* Renderer::getWindow()
{
	return window;
}