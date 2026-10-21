#include <glad/glad.h>       // 1
#include <GLFW/glfw3.h>      // 2
#include <iostream>
#include "window.hpp"

int main() {
    Window* window = new Window();
    delete(window);
    return 0;
}