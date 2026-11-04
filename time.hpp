#pragma once

/// <summary>
/// Stores timing values shared by the application.
/// </summary>
class Time {
public:
	Time() = delete;
	inline static float s_DeltaTime = 0.0f;
	inline static double s_Time = 0.0f;
	static void SetDeltaTime(float dt);
};