#pragma once

#include "shader.hpp"
#include "time.hpp"
#include "texture.hpp"
#include <memory>
#include "mesh.hpp"
#include <glm/glm.hpp>
#include "transform.hpp"
#include "input.hpp"

class RenderObject {
public:
	void setShader(std::shared_ptr<Shader> shader);
	void setMesh(std::shared_ptr<Mesh> mesh);
	void setTexture(std::shared_ptr<Texture> texture);

	/// <summary>
	/// Updates this render object each frame. Override in derived classes.
	/// </summary>
	virtual void update() = 0;

	/// <summary>
	/// Called just before drawing this render object. Override in derived classes.
	/// </summary>
	virtual void beforeDraw() = 0;

	virtual void awake() = 0;

	Transform m_transform;

	std::shared_ptr<Shader> getShader();
	std::shared_ptr<Mesh> getMesh();
	std::shared_ptr<Texture> getTexture();

	glm::mat4 getModelMatrix();

	virtual ~RenderObject() = default;
private:
	std::shared_ptr<Shader> m_shader = nullptr;
	std::shared_ptr<Mesh> m_mesh = nullptr;
	std::shared_ptr<Texture> m_texture = nullptr;
};