#pragma once

#include <glm/glm.hpp>

/// <summary>
/// Stores the position, texture coordinates, and normal of a vertex.
/// </summary>
struct Vertex {
	glm::vec3 position;
	glm::vec2 uvCoords;
	glm::vec3 normal;
};