#pragma once

#include "shader.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include "mesh.hpp"

class RenderObject {
public:
	void setShader(std::shared_ptr<Shader> shader);
	void setMesh(std::shared_ptr<Mesh> mesh);

	/// <summary>
	/// Updates this render object each frame. Override in derived classes.
	/// </summary>
	virtual void update() = 0;

	/// <summary>
	/// Called just before drawing this render object. Override in derived classes.
	/// </summary>
	virtual void beforeDraw() = 0;

	std::shared_ptr<Shader> getShader();
	std::shared_ptr<Mesh> getMesh();

	virtual ~RenderObject() = default;
private:
	std::shared_ptr<Shader> m_shader = nullptr;
	std::shared_ptr<Mesh> m_mesh = nullptr;
};