#pragma once

#include "scene_element.hpp"

class LightSourceElement : public SceneElement {
public:
	void Update() override;
	void BeforeDraw() override;
	void Awake() override;
	glm::vec3 GetLightPosition() const;
	glm::vec3 GetLightColor() const;
private:
	glm::vec3 m_lightColor{ 0.0f,1.0f,0.0f };
};