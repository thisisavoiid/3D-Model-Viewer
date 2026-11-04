#pragma once

#include "scene_element.hpp"
#include "cubemap.hpp"
#include <memory>

class SkyboxElement : public SceneElement {
public:
	void BeforeDraw() override;
	void AfterDraw() override;
	void Awake(Engine& engine) override;
	void Update() override;
	void SetCubeMap(std::shared_ptr<CubeMap> cubeMap);
	glm::mat4 GetViewMatrix(const glm::mat4& view) const override;

	SkyboxElement(
		std::filesystem::path right,
		std::filesystem::path left,
		std::filesystem::path top,
		std::filesystem::path bottom,
		std::filesystem::path front,
		std::filesystem::path back
	);
private:
	std::shared_ptr<CubeMap> m_cubeMap = nullptr;
};