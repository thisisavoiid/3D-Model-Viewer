#include "window.hpp"
#include <iostream>

void Window::onResize(GLFWwindow*, int w, int h)
{
	glViewport(0, 0, w, h);
}

void Window::processInput(GLFWwindow* win)
{
    if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(win, true);

    //if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
    //    switchColor();
}

Window::Window()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "3D Model Viewer", nullptr, nullptr);

	if (!window) {
		std::cerr << "Window could not be initialized!\n";
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "GLAD could not be initialized!\n";
		glfwTerminate();
		return;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, &Window::onResize);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		float a = abs(sin(glfwGetTime() * 0.5f + 0.5f));
		glClearColor(1.0f, a, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

Window::~Window()
{
	std::cout << "Window has been terminated!\n";
	glfwTerminate();
}
