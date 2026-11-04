#include "input.hpp"
#include "windows.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/// <summary>
/// Updates the current and previous keyboard state snapshots.
/// </summary>
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

/// <summary>
/// Updates the cursor position and calculates its movement delta.
/// </summary>
/// <param name="xpos">
/// The new cursor x-coordinate.
/// </param>
/// <param name="ypos">
/// The new cursor y-coordinate.
/// </param>
void Input::UpdateCursorPosition(double xpos, double ypos)
{
	glm::vec2 prevCursorPos = s_CursorPos;

	s_CursorPos.x = xpos;
	s_CursorPos.y = ypos;

	s_CursorDelta.x = s_CursorPos.x - prevCursorPos.x;
	s_CursorDelta.y = s_CursorPos.y - prevCursorPos.y;
}

/// <summary>
/// Sets the cursor mode for the current GLFW window.
/// </summary>
/// <param name="mode">
/// The GLFW cursor mode to apply.
/// </param>
void Input::SetCursorMode(int mode)
{
	GLFWwindow* currentWin = glfwGetCurrentContext();
	glfwSetInputMode(currentWin, GLFW_CURSOR, mode);
}

/// <summary>
/// Gets the cursor mode of the current GLFW window.
/// </summary>
/// <returns>
/// The current GLFW cursor mode.
/// </returns>
int Input::GetCursorMode()
{
	GLFWwindow* currentWin = glfwGetCurrentContext();
	return glfwGetInputMode(currentWin, GLFW_CURSOR);
}

/// <summary>
/// Sets the cursor position in the current GLFW window.
/// </summary>
/// <param name="xpos">
/// The target cursor x-coordinate.
/// </param>
/// <param name="ypos">
/// The target cursor y-coordinate.
/// </param>
void Input::SetCursorPosition(double xpos, double ypos)
{
	GLFWwindow* currentWin = glfwGetCurrentContext();
	glfwSetCursorPos(currentWin, xpos, ypos);
}

/// <summary>
/// Determines whether a key is currently held down.
/// </summary>
/// <param name="key">
/// The key to query.
/// </param>
/// <returns>
/// True if the key is currently held; otherwise, false.
/// </returns>
bool Input::IsKeyHeld(Key key)
{
	const int keyCode = static_cast<int>(key);
	return s_CurrentKeys[keyCode];
}

/// <summary>
/// Determines whether a key was released during the current update.
/// </summary>
/// <param name="key">
/// The key to query.
/// </param>
/// <returns>
/// True if the key was released; otherwise, false.
/// </returns>
bool Input::IsKeyReleased(Key key)
{
	const int keyCode = static_cast<int>(key);
	return s_CurrentKeys[keyCode] == false && s_PreviousKeys[keyCode] == true;
}

/// <summary>
/// Determines whether a key was pressed during the current update.
/// </summary>
/// <param name="key">
/// The key to query.
/// </param>
/// <returns>
/// True if the key was pressed; otherwise, false.
/// </returns>
bool Input::IsKeyPressed(Key key)
{
	const int keyCode = static_cast<int>(key);
	return s_CurrentKeys[keyCode] == true && s_PreviousKeys[keyCode] == false;
}

/// <summary>
/// Gets the cursor movement since the previous input update.
/// </summary>
/// <returns>
/// The cursor movement delta.
/// </returns>
glm::vec2 Input::GetCursorDelta()
{
	return s_CursorDelta;
}

/// <summary>
/// Gets the current cursor position.
/// </summary>
/// <returns>
/// The cursor position.
/// </returns>
glm::vec2 Input::GetCursorPos()
{
	return s_CursorPos;
}

