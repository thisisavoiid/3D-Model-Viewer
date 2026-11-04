#pragma once

#include <glm/glm.hpp>
#include <vector>

/// <summary>
/// Stores an object's position, rotation, and scale in the scene.
/// </summary>
struct Transform {
	glm::vec3 position{ 0.0f,0.0f,0.0f };
	glm::vec3 rotation{ 0.0f,0.0f,0.0f };
	glm::vec3 scale{ 1.0f,1.0f,1.0f };
};