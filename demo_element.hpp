#pragma once

#include "scene_element.hpp"
#include "engine.hpp"

/// <summary>
/// Represents the demo scene element used to demonstrate movement and rotation.
/// </summary>
class DemoElement : public SceneElement {
public: 
	void Update() override;
	void BeforeDraw() override;
	void Awake(Engine& engine) override;

private:
	float m_speed = 2.5f;
};