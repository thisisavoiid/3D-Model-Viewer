#include "window.hpp"
#include <iostream>
#include <filesystem>
#include "shader.hpp"
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

GLFWwindow* Window::m_window = nullptr;
//
//const char* vertexShader = R"GLSL(
//	#version 330 core
//	layout(location=0) in vec3 aPos;
//	void main() {
//		gl_Position = vec4(aPos, 
//	}
//)GLSL";
//
//const char* fragmentShader = R"GLSL(
//	#version 330 core
//	out vec4 FragColor;
//	void main(){
//		FragColor = vec4(1.0, 0.5, 0.2, 1.0); 
//	}
//)GLSL";

void Window::onResize(GLFWwindow*, int w, int h)
{
	glViewport(0, 0, w, h);
}

void Window::processInput(GLFWwindow* win)
{
	if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(win, true);
}

void Window::setup()
{
	std::cout << "Setting up window...\n";

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(800, 600, "3D Model Viewer", nullptr, nullptr);

	if (!m_window) {
		std::cerr << "Window could not be initialized!\n";
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "GLAD could not be initialized!\n";
		glfwTerminate();
		return;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(m_window, &Window::onResize);

	std::cout << "Window set up OK\n";
}

void Window::run() {
	const std::filesystem::path shaderDirectory = "shaders/test";
	const std::string vertexPath =
		(shaderDirectory / "test.vert").string();
	const std::string fragmentPath =
		(shaderDirectory / "test.frag").string();

	Shader shader(vertexPath.c_str(), fragmentPath.c_str());

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f, 
		0.5f,  0.5f, -0.5f, 
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f, 
		0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f,

		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		0.5f, -0.5f, -0.5f, 
		0.5f,  0.5f, -0.5f, 
		0.5f,  0.5f,  0.5f, 
		0.5f, -0.5f,  0.5f, 

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f,  0.5f, 
		-0.5f, -0.5f,  0.5f,
		0.5f,  0.5f, -0.5f, 
		-0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f, 
	};
	// index data
	unsigned int indices[] = {
		// front and back
		0, 3, 2,
		2, 1, 0,
		4, 5, 6,
		6, 7 ,4,
		// left and right
		11, 8, 9,
		9, 10, 11,
		12, 13, 14,
		14, 15, 12,
		// bottom and top
		16, 17, 18,
		18, 19, 16,
		20, 21, 22,
		22, 23, 20
	};

	unsigned vao, vbo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int ebo;

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(m_window)) {
		processInput(m_window);

		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();

		glm::mat4 model(1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3));
		glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1, 1, 1));
		model = glm::scale(model, glm::vec3(0.5f));

		shader.setMat4("uModel", model);
		shader.setMat4("uView", view);
		shader.setMat4("uProj", proj);

		shader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glDrawElements(GL_TRIANGLES, sizeof(indices)/3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	//delete(camera);
	//camera = nullptr;
}

Window::Window()
{
	setup();
}

Window::~Window()
{
	if (m_window)
		glfwDestroyWindow(m_window);

	m_window = nullptr;

	std::cout << "Window has been terminated!\n";

	glfwTerminate();
}
