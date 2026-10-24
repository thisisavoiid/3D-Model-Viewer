#pragma once

#include "render_object.hpp"
#include <vector>
#include <memory>
#include "window.hpp"

class Engine {
public:
	void loadObject(std::shared_ptr<RenderObject> ro);
	void setWindow(std::shared_ptr<Window> window);
	void run();
private:
	double m_lastUpdate = 0.0;
	std::vector<std::shared_ptr<RenderObject>> m_objects;
	std::shared_ptr<Window> m_window = nullptr;
	void onUpdate();
	void renderObject(std::shared_ptr<RenderObject> ro);
};