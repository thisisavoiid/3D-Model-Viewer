#include "window.hpp"
#include <iostream>
#include <filesystem>
#include "shader.hpp"

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

	float v[] = {
	-0.5f,-0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	0.0f,0.5f,0.0f
	};

	unsigned vao, vbo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(m_window)) {
		processInput(m_window);

		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();

		shader.setFloat("uTime", static_cast<float>(glfwGetTime()));
		shader.setFloat("uSpeed", std::abs(std::sin(glfwGetTime() * 0.1f)) * 2.5f);
		shader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));
		shader.setVec3("vColor", glm::vec3(1.0f, 0.0f, 1.0f));

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
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
