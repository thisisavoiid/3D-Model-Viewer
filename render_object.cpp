#include "render_object.hpp"
#include "shader.hpp"
#include <memory>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
void RenderObject::setShader(std::shared_ptr<Shader> shader)
{
	m_shader = shader;
}

void RenderObject::setMesh(std::shared_ptr<Mesh> mesh)
{
	m_mesh = mesh;
}

std::shared_ptr<Mesh> RenderObject::getMesh() {
	return m_mesh;
}

glm::mat4 RenderObject::getModelMatrix()
{
	glm::mat4 model(1.0f);

	model = glm::translate(model, m_transform.position);

	model = glm::rotate(
		model,
		m_transform.rotation.x,
		glm::vec3(1.0f, 0.0f, 0.0f)
	);

	model = glm::rotate(
		model,
		m_transform.rotation.y,
		glm::vec3(0.0f, 1.0f, 0.0f)
	);

	model = glm::rotate(
		model,
		m_transform.rotation.z,
		glm::vec3(0.0f, 0.0f, 1.0f)
	);

	model = glm::scale(
		model,
		m_transform.scale
	);

	return std::move(model);
}

std::shared_ptr<Shader> RenderObject::getShader()
{
	return m_shader;
}


