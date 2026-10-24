#include "time.h"
#include <iostream>

float Time::deltaTime = 0.0f;
double Time::time = 0.0f;

/// <summary>
/// Sets the current delta time and updates the total uptime.
/// </summary>
/// <param name="dt">
/// The delta time value to set for the current frame.
/// </param>
void Time::setDeltaTime(float dt)
{
	Time::deltaTime = dt;
	std::cout << "Delta Time: " << Time::deltaTime << "\n";

	Time::time += dt;
	std::cout << "Uptime: " << Time::time << "\n";
}