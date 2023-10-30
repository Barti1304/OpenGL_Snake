#include "Renderer.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Renderer::Renderer(int windowWidth, int windowHeight, const char* windowTitle, int mapW, int mapH, int dims)
{
	dimensions = dims;

	this->initWindow(windowWidth, windowHeight, windowTitle);
	this->initShader();
	this->initVAO();

	mapWidth = mapW;
	mapHeight = mapH;

	if (dims != 2 && dims != 3)
		exit(-1);
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

	if (dimensions == 3)
		glEnable(GL_DEPTH_TEST);
}

void Renderer::initShader()
{
	if (dimensions == 2)
		shader = new Shader("./src/shader2D.vert", "./src/shader2D.frag");
	else
		shader = new Shader("./src/shader3D.vert", "./src/shader3D.frag");
	
	shader->use();
}

void Renderer::initVAO()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	if (dimensions == 2)
	{
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	else
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

	}
}

void Renderer::renderSquare(int x, int y, const float* color) const
{
	float xPos = -1 + (float(x) / mapWidth) * 2;
	float yPos = 1 - (float(y) / mapHeight) * 2;
	float zPos = -1 + (float(1) / mapWidth) * 2;
	float width = (float(1) / mapHeight) * 2;
	float height = (float(1) / mapWidth) * 2;
	float lenght = 0.1f;

	// NAPRAWIÆ BRAK 3D - POWÓD JESZCZE NIEZNANY
	if (dimensions == 2)
	{
		float coords[]
		{
			xPos, yPos,							color[0], color[1], color[2],
			xPos, yPos - height,				color[0], color[1], color[2],
			xPos + width, yPos - height,		color[0], color[1], color[2],
			xPos + width, yPos,					color[0], color[1], color[2],
		};

		unsigned int indices[]
		{
			0, 1, 2,
			0, 3, 2
		};

		glBindVertexArray(vao);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_DYNAMIC_DRAW);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	else
	{
		float coords[]
		{
			xPos, yPos, zPos,									color[0], color[1], color[2],
			xPos + width, yPos, zPos,							color[0], color[1], color[2],
			xPos, yPos - height, zPos,							color[0], color[1], color[2],
			xPos + width, yPos - height, zPos,					color[0], color[1], color[2],
			xPos, yPos, zPos + lenght,							color[0], color[1], color[2],
			xPos + width, yPos, zPos + lenght,					color[0], color[1], color[2],
			xPos, yPos - height, zPos + lenght,					color[0], color[1], color[2],
			xPos + width, yPos - height, zPos + lenght,			color[0], color[1], color[2]
		};

		unsigned int indices[]
		{
			0, 1, 2,
			1, 2, 3,
			4, 5, 6,
			5, 6, 7,
			0, 2, 4,
			2, 4, 6,
			1, 3, 5,
			3, 5, 7,
			0, 1, 4,
			1, 4, 5,
			2, 3, 6,
			3, 6, 7
		};

		glBindVertexArray(vao);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_DYNAMIC_DRAW);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
		projection = glm::perspective(glm::radians(45.0f), float(mapWidth / mapHeight), 0.1f, 100.0f);

		glUniformMatrix4fv(glGetUniformLocation(shader->id(), "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shader->id(), "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader->id(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
}

GLFWwindow* Renderer::getWindow()
{
	return window;
}

void Renderer::updateTitleBar(int src)
{
	std::string title = "OpenGL - Snake | Score: " + std::to_string(src) + 
		" | Elapsed time: " + std::to_string((int)(glfwGetTime()) / 60) + ':';

	title += (std::to_string((int)(glfwGetTime()) % 60).size() == 1) ? "0" : "";
	title += std::to_string((int)(glfwGetTime()) % 60);

	glfwSetWindowTitle(window, title.c_str());
}