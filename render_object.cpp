#include "render_object.hpp"
#include "shader.hpp"
#include <memory>
#include <iostream>

/// <summary>
/// Sets the shader for this render object.
/// </summary>
/// <param name="shader">
/// The shader to use when rendering this object.
/// </param>
void RenderObject::setShader(std::shared_ptr<Shader> shader)
{
	m_shader = shader;
}

/// <summary>
/// Sets the vertices for this render object.
/// </summary>
/// <param name="vertices">
/// A vector containing the vertices of this object.
/// </param>
void RenderObject::setVertices(std::vector<float> vertices)
{
	m_vertices = std::move(vertices);
}

/// <summary>
/// Sets the indices for this render object.
/// </summary>
/// <param name="indices">
/// A vector containing the indices of this object.
/// </param>
void RenderObject::setIndices(std::vector<unsigned int> indices) {
	m_indices = std::move(indices);
}

/// <summary>
/// Gets the currently applied shader of this render object.
/// </summary>
/// <returns>
/// A shared pointer referencing the currently set shader of this render object.
/// </returns>
std::shared_ptr<Shader> RenderObject::getShader()
{
	return m_shader;
}

/// <summary>
/// Gets the vertices of this render object.
/// </summary>
/// <returns>
/// A float vector containing the vertices of this render object.
/// </returns>
std::vector<float> RenderObject::getVertices()
{
	return m_vertices;
}

/// <summary>
/// Gets the indices of this render object.
/// </summary>
/// <returns>
/// An unsigned int vector containing the indices of this render object.
/// </returns>
std::vector<unsigned int> RenderObject::getIndices()
{
	return m_indices;
}
