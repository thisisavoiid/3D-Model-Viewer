#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window();
    ~Window();
private:
    static void onResize(GLFWwindow*, int w, int h);
    static void processInput(GLFWwindow* win);
};