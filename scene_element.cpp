#include "scene_element.hpp"
#include "shader.hpp"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>

/// <summary>
/// Assigns the shader used to render this scene element.
/// </summary>
/// <param name="shader">
/// The shader to assign.
/// </param>
void SceneElement::SetShader(std::shared_ptr<Shader> shader)
{
	m_shader = shader;
}

/// <summary>
/// Assigns the mesh used to render this scene element.
/// </summary>
/// <param name="mesh">
/// The mesh to assign.
/// </param>
void SceneElement::SetMesh(std::shared_ptr<Mesh> mesh)
{
	m_mesh = mesh;
}

/// <summary>
/// Assigns the texture used by this scene element.
/// </summary>
/// <param name="texture">
/// The texture to assign.
/// </param>
void SceneElement::SetTexture(std::shared_ptr<Texture> texture)
{
	m_texture = texture;
}

void SceneElement::AfterDraw()
{
}

/// <summary>
/// Gets the mesh assigned to this scene element.
/// </summary>
/// <returns>
/// The assigned mesh.
/// </returns>
std::shared_ptr<Mesh> SceneElement::GetMesh() const {
	return m_mesh;
}

glm::mat4 SceneElement::GetViewMatrix(const glm::mat4& view) const {
	return view;
}

/// <summary>
/// Gets the texture assigned to this scene element.
/// </summary>
/// <returns>
/// The assigned texture.
/// </returns>
std::shared_ptr<Texture> SceneElement::GetTexture() const
{
	return m_texture;
}

/// <summary>
/// Builds the model matrix from the element's transform.
/// </summary>
/// <returns>
/// The model transformation matrix.
/// </returns>
glm::mat4 SceneElement::GetModelMatrix() const
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

/// <summary>
/// Gets the shader assigned to this scene element.
/// </summary>
/// <returns>
/// The assigned shader.
/// </returns>
std::shared_ptr<Shader> SceneElement::GetShader() const
{
	return m_shader;
}


