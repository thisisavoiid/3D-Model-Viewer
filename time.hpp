#pragma once

class Time {
public:
	Time() = delete;
	inline static float deltaTime = 0.0f;
	inline static double time = 0.0f;
	static void setDeltaTime(float dt);
};