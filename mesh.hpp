#pragma once

#include <vector>

class Mesh {
public:
	void setVertices(std::vector<float> vertices);
	void setIndices(std::vector<unsigned int> indices);
	void genBuffers();
	Mesh();
	std::vector<float> getVertices();
	std::vector<unsigned int> getIndices();
	unsigned int getEboBuffer();
private: 
	unsigned m_vao, m_vbo;
	unsigned int m_ebo;
	std::vector<unsigned int> m_indices;
	std::vector<float> m_vertices;
};