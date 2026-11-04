#include "skybox_element.hpp"
#include "mesh.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

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

void SkyboxElement::BeforeDraw()
{
	glDepthMask(GL_FALSE);

	if (m_cubeMap != nullptr)
		m_cubeMap->Use();

	std::shared_ptr<Shader> shader = this->GetShader();

	if (shader != nullptr)
		shader->SetInt("uSkybox", 0);
}

void SkyboxElement::AfterDraw()
{
	glDepthMask(GL_TRUE);
}

void SkyboxElement::Awake(Engine& engine)
{
}

void SkyboxElement::Update()
{
}

void SkyboxElement::SetCubeMap(std::shared_ptr<CubeMap> cubeMap)
{
	if (cubeMap == nullptr)
		return;
	
	m_cubeMap = cubeMap;
}

glm::mat4 SkyboxElement::GetViewMatrix(const glm::mat4& view) const
{
	return glm::mat4(glm::mat3(view));
}

