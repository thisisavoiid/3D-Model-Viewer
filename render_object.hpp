#pragma once

#include "shader.hpp"
#include "time.hpp"
#include <memory>
#include "mesh.hpp"
#include <glm/glm.hpp>
#include "transform.hpp"

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

	Transform m_transform;

	std::shared_ptr<Shader> getShader();
	std::shared_ptr<Mesh> getMesh();
	glm::mat4 getModelMatrix();
	virtual ~RenderObject() = default;

	//glm::vec3 m_position{ 0,0,0 };
	//glm::vec3 m_rotation{ 0,0,0 };
	//glm::vec3 m_scale{ 0.5f,0.5f,0.5f };
private:
	std::shared_ptr<Shader> m_shader = nullptr;
	std::shared_ptr<Mesh> m_mesh = nullptr;
};