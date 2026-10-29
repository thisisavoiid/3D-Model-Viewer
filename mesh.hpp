#pragma once

#include <vector>
#include <glm/glm.hpp>

class Mesh {
public:
	void draw();
	Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> normals, std::vector<float> uvs);
	unsigned int getEboBuffer();
private: 
	int m_indexCount;
	unsigned m_vao;
	unsigned m_verticesVbo;
	unsigned m_normalVbo;
	unsigned m_uvVbo;
	unsigned int m_indicesEbo;
};