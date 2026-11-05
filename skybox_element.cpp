#include "skybox_element.hpp"
#include "mesh.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

/// <summary>
/// Creates the vertex and index data for a skybox cube.
/// </summary>
/// <returns>
/// The mesh data for the skybox cube.
/// </returns>
MeshData CreateSkyboxMesh()
{
	MeshData data;
	data.vertices = {
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f
	};

	data.indices = {
		0, 1, 2, 2, 3, 0,
		4, 5, 1, 1, 0, 4,
		7, 6, 5, 5, 4, 7,
		3, 2, 6, 6, 7, 3,
		4, 0, 3, 3, 7, 4,
		1, 5, 6, 6, 2, 1
	};

	return data;
}

/// <summary>
/// Creates a skybox element from six cubemap face images.
/// </summary>
/// <param name="right">
/// The path to the right face image.
/// </param>
/// <param name="left">
/// The path to the left face image.
/// </param>
/// <param name="top">
/// The path to the top face image.
/// </param>
/// <param name="bottom">
/// The path to the bottom face image.
/// </param>
/// <param name="front">
/// The path to the front face image.
/// </param>
/// <param name="back">
/// The path to the back face image.
/// </param>
SkyboxElement::SkyboxElement(
	std::filesystem::path right,
	std::filesystem::path left,
	std::filesystem::path top,
	std::filesystem::path bottom,
	std::filesystem::path front,
	std::filesystem::path back
)
{
	std::shared_ptr<CubeMap> cubeMap = std::make_shared<CubeMap>(
		right,
		left,
		top,
		bottom,
		front,
		back
	);

	SetCubeMap(cubeMap);
	SetMesh(std::make_shared<Mesh>(CreateSkyboxMesh()));
}

/// <summary>
/// Configures depth testing and the cubemap before drawing the skybox.
/// </summary>
void SkyboxElement::BeforeDraw()
{
	glDepthMask(GL_FALSE);

	if (m_cubeMap != nullptr)
		m_cubeMap->Use();

	std::shared_ptr<Shader> shader = this->GetShader();

	if (shader != nullptr)
		shader->SetInt("uSkybox", 0);
}

/// <summary>
/// Restores depth writing after drawing the skybox.
/// </summary>
void SkyboxElement::AfterDraw()
{
	glDepthMask(GL_TRUE);
}

/// <summary>
/// Initializes the skybox during scene setup.
/// </summary>
/// <param name="engine">
/// The engine that owns the scene.
/// </param>
void SkyboxElement::Awake(Engine& engine)
{
}

/// <summary>
/// Updates the skybox for the current frame.
/// </summary>
void SkyboxElement::Update()
{
}

/// <summary>
/// Assigns the cubemap used to render the skybox.
/// </summary>
/// <param name="cubeMap">
/// The cubemap to assign.
/// </param>
void SkyboxElement::SetCubeMap(std::shared_ptr<CubeMap> cubeMap)
{
	if (cubeMap == nullptr)
		return;
	
	m_cubeMap = cubeMap;
}

/// <summary>
/// Removes camera translation from the view matrix for skybox rendering.
/// </summary>
/// <param name="view">
/// The view matrix supplied by the active camera.
/// </param>
/// <returns>
/// The view matrix without camera translation.
/// </returns>
glm::mat4 SkyboxElement::GetViewMatrix(const glm::mat4& view) const
{
	return glm::mat4(glm::mat3(view));
}

