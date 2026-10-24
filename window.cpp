#include "window.hpp"
#include <iostream>

GLFWwindow* Window::m_window = nullptr;

void Window::onResize(GLFWwindow*, int w, int h)
{
	glViewport(0, 0, w, h);
}

/// <summary>
/// Gets the underlying GLFW window instance.
/// </summary>
/// <returns>
/// A pointer to the GLFW window used by this Window object.
/// </returns>
GLFWwindow* Window::getGlfwWindowInstance()
{
	return m_window;
}

/// <summary>
/// Constructs a new Window with the given title, width, and height.
/// Initializes GLFW, creates the window, loads GLAD, and sets up the viewport.
/// </summary>
/// <param name="title">
/// The title of the window.
/// </param>
/// <param name="width">
/// The initial width of the window.
/// </param>
/// <param name="height">
/// The initial height of the window.
/// </param>
Window::Window(std::string title, int width, int height)
{
	std::cout << "Setting up window -\n";
	std::cout << "TITLE = " << title << "\n";
	std::cout << "WIDTH = " << width << "\n";
	std::cout << "HEIGHT = " << height << "\n";

	std::cout << "Setting window hints -\n";

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	std::cout << "Window hints set! -\n";

	std::cout << "Initializing window -\n";

	m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

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

	glViewport(0, 0, width, height);

	glfwSetFramebufferSizeCallback(m_window, &Window::onResize);

	std::cout << "Window and viewport setup finished! -\n";
}

/// <summary>
/// Destroys the window and terminates GLFW.
/// </summary>
Window::~Window()
{
	std::cout << "Terminating window -\n";

	if (m_window)
		glfwDestroyWindow(m_window);

	m_window = nullptr;

	std::cout << "Window has been terminated! -\n";

	glfwTerminate();
}