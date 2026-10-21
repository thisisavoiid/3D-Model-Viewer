#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
    void run();
    Window();
    ~Window();
private:
    static GLFWwindow* m_window;
    static void onResize(GLFWwindow*, int w, int h);
    static void processInput(GLFWwindow* win);
    static void setup();
    //static void draw();
};