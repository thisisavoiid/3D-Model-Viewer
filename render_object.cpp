#include "render_object.hpp"
#include "shader.hpp"
#include <memory>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
void RenderObject::SetShader(std::shared_ptr<Shader> shader)
{
	m_shader = shader;
}

void RenderObject::SetMesh(std::shared_ptr<Mesh> mesh)
{
	m_mesh = mesh;
}

void RenderObject::SetTexture(std::shared_ptr<Texture> texture)
{
	m_texture = texture;
}

std::shared_ptr<Mesh> RenderObject::GetMesh() const {
	return m_mesh;
}

std::shared_ptr<Texture> RenderObject::GetTexture() const
{
	return m_texture;
}

glm::mat4 RenderObject::GetModelMatrix() const
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

	return model;
}

std::shared_ptr<Shader> RenderObject::GetShader() const
{
	return m_shader;
}


