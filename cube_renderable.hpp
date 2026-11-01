#pragma once

#include "render_object.hpp"

class CubeRenderable : public RenderObject {
public: 
	void Update() override;
	void BeforeDraw() override;
	void Awake() override;

private:
	float m_speed = 2.5f;
};