#pragma once

#include <vector>
#include <glm/glm.hpp>

struct MeshData {
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> normals;
	std::vector<float> uvs;
};

class Mesh {
public:
	void Draw();
	Mesh(MeshData data);
	~Mesh();
	unsigned int GetEboBuffer() const;
private: 
	int m_indexCount;
	unsigned m_vao;
	unsigned m_verticesVbo;
	unsigned m_normalVbo;
	unsigned m_uvVbo;
	unsigned int m_indicesEbo;
};