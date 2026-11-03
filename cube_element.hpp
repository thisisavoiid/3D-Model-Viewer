#pragma once

#include "scene_element.hpp"

class CubeElement : public SceneElement {
public: 
	void Update() override;
	void BeforeDraw() override;
	void Awake() override;

private:
	float m_speed = 2.5f;
};