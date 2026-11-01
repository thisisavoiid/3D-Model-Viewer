#include "input.hpp"
#include "windows.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Input::UpdateKeyInput()
{
	s_PreviousKeys = s_CurrentKeys;

	auto fetch = [](int vKey) {
		return (GetAsyncKeyState(vKey) & 0x8000) != 0;
	};

	for (int key = 0; key < 256; ++key) {
		s_CurrentKeys[key] = fetch(key);
	}
}

void Input::UpdateCursorPosition(double xpos, double ypos)
{
	glm::vec2 prevCursorPos = std::move(s_CursorPos);

	s_CursorPos.x = xpos;
	s_CursorPos.y = ypos;

	s_CursorDelta.x = s_CursorPos.x - prevCursorPos.x;
	s_CursorDelta.y = s_CursorPos.y - prevCursorPos.y;
}

void Input::SetCursorMode(int mode)
{
	GLFWwindow* currentWin = glfwGetCurrentContext();
	glfwSetInputMode(currentWin, GLFW_CURSOR, mode);
}

//void Input::SetCursorMode(CursorMode mode)
//{
//	GLFWwindow* currentWin = glfwGetCurrentContext();
//	glfwSetInputMode(currentWin, GLFW_CURSOR, static_cast<int>(mode));
//}

bool Input::IsKeyHeld(Key key)
{
	const int keyCode = static_cast<int>(key);
	return s_CurrentKeys[keyCode];
}

bool Input::IsKeyReleased(Key key)
{
	const int keyCode = static_cast<int>(key);
	return s_CurrentKeys[keyCode] == false && s_PreviousKeys[keyCode] == true;
}

bool Input::IsKeyPressed(Key key)
{
	const int keyCode = static_cast<int>(key);
	return s_CurrentKeys[keyCode] == true && s_PreviousKeys[keyCode] == false;
}

glm::vec2 Input::GetCursorDelta()
{
	return s_CursorDelta;
}

glm::vec2 Input::GetCursorPos()
{
	return s_CursorPos;
}

