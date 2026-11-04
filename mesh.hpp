#pragma once

#include <vector>
#include <glm/glm.hpp>

/// <summary>
/// Stores the vertex attributes and indices used to construct a mesh.
/// </summary>
struct MeshData {
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> normals;
	std::vector<float> uvs;
};

/// <summary>
/// Manages the OpenGL buffers required to draw a mesh.
/// </summary>
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