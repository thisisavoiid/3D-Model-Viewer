#pragma once

#include "shader.hpp"
#include <vector>
#include <iostream>
#include <memory>

class RenderObject {
public:
	void setShader(std::shared_ptr<Shader> shader);
	void setVertices(std::vector<float> vertices);
	void setIndices(std::vector<unsigned int> indices);

	/// <summary>
	/// Updates this render object each frame. Override in derived classes.
	/// </summary>
	virtual void update() {};

	/// <summary>
	/// Called just before drawing this render object. Override in derived classes.
	/// </summary>
	virtual void beforeDraw() {};

	std::shared_ptr<Shader> getShader();
	std::vector<float> getVertices();
	std::vector<unsigned int> getIndices();
private:
	std::shared_ptr<Shader> m_shader = nullptr;
	std::vector<unsigned int> m_indices;
	std::vector<float> m_vertices;
};