#pragma once

#include "scene_element.hpp"

/// <summary>
/// Represents a light source scene element with a position and color.
/// </summary>
class LightSourceElement : public SceneElement, public std::enable_shared_from_this<LightSourceElement> {
public:
	void Update() override;
	void BeforeDraw() override;
	void Awake(Engine& engine) override;
	LightSourceElement(glm::vec3 color);
	glm::vec3 GetLightPosition() const;
	glm::vec3 GetLightColor() const;
private:
	glm::vec3 m_lightColor{ 1.0f,1.0f,1.0f };
};