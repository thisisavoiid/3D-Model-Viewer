#pragma once

#include "render_object.hpp"

class CubeRenderable : public RenderObject {
public: 
	void update() override;
	void beforeDraw() override;
};