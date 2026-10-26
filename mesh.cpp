#include "mesh.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Mesh::setVertices(std::vector<float> vertices)
{
	m_vertices = std::move(vertices);
}

void Mesh::setIndices(std::vector<unsigned int> indices)
{
	m_indices = std::move(indices);
}

Mesh::Mesh()
{
	genBuffers();
}

std::vector<float> Mesh::getVertices()
{
	return m_vertices;
}

std::vector<unsigned int> Mesh::getIndices()
{
	return m_indices;
}

unsigned int Mesh::getEboBuffer()
{
	return m_ebo;
}

void Mesh::genBuffers()
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);
}
