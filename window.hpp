#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    GLFWwindow* getGlfwWindowInstance();
    Window(std::string title, int width, int height);
    ~Window();
private:
    static GLFWwindow* m_window;
    static void onResize(GLFWwindow*, int w, int h);
    //static void processInput(GLFWwindow* win);
};