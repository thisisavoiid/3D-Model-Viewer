#include "time.hpp"
#include <iostream>

/// <summary>
/// Sets the current delta time and updates the total uptime.
/// </summary>
/// <param name="dt">
/// The delta time value to set for the current frame.
/// </param>
void Time::SetDeltaTime(float dt)
{
	Time::s_DeltaTime = dt;
	Time::s_Time += dt;
}