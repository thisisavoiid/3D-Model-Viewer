#include "mesh.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Mesh::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_verticesVbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesEbo);
	
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
}

Mesh::Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> normals, std::vector<float> uvs)
{
    m_indexCount = indices.size();

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // VERTEX POSITIONS
    glGenBuffers(1, &m_verticesVbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_verticesVbo);

    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(float),
        vertices.data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE,
        3 * sizeof(float), (void*)0
    );

    glEnableVertexAttribArray(0);

    // INDICES
    glGenBuffers(1, &m_indicesEbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesEbo);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int),
        indices.data(),
        GL_STATIC_DRAW
    );

    // NORMALS
    glGenBuffers(1, &m_normalVbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_normalVbo);

    glBufferData(
        GL_ARRAY_BUFFER,
        normals.size() * sizeof(float),
        normals.data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE,
        3 * sizeof(float), (void*)0
    );

    glEnableVertexAttribArray(1);

    // UVS
    glGenBuffers(1, &m_uvVbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_uvVbo);

    glBufferData(
        GL_ARRAY_BUFFER,
        uvs.size() * sizeof(float),
        uvs.data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        2, 2, GL_FLOAT, GL_FALSE,
        2 * sizeof(float), (void*)0
    );

    glEnableVertexAttribArray(2);
}

unsigned int Mesh::getEboBuffer()
{
	return m_indicesEbo;
}