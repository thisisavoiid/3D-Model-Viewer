#include "input.hpp"
#include "windows.h"

void Input::Update()
{
	s_PreviousKeys = s_CurrentKeys;

	auto fetch = [](int vKey) {
		return (GetAsyncKeyState(vKey) & 0x8000) != 0;
	};

	for (int key = 0; key < 256; ++key) {
		s_CurrentKeys[key] = fetch(key);
	}
}

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

