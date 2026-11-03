#pragma once

#include "scene_element.hpp"
#include <vector>
#include <memory>
#include "window.hpp"
#include "camera.hpp"

class Engine {
public:
	void LoadObject(std::shared_ptr<SceneElement> ro);
	void SetWindow(std::shared_ptr<Window> window);
	void SetCamera(std::shared_ptr<Camera> camera);
	void Run();
private:
	double m_lastUpdate = 0.0;
	std::vector<std::shared_ptr<SceneElement>> m_objects;
	std::shared_ptr<Window> m_window = nullptr;
	std::shared_ptr<Camera> m_camera = nullptr;
	void ProcessInput(GLFWwindow* window);
	void OnUpdate();
	void OnAwake();
	void RenderSingleObject(std::shared_ptr<SceneElement> ro);
};