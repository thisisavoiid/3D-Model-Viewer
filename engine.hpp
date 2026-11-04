#pragma once

#include "scene_element.hpp"
#include <vector>
#include <memory>
#include "window.hpp"
#include "camera_element.hpp"
#include "light_source_element.hpp"

/// <summary>
/// Coordinates scene elements, rendering, input updates, and the application loop.
/// </summary>
class Engine {
public:
	void LoadObject(std::shared_ptr<SceneElement> ro);
	void SetWindow(std::shared_ptr<Window> window);
	void SetCamera(std::shared_ptr<CameraElement> camera);
	void SetLightSource(std::shared_ptr<LightSourceElement> source);
	void Run();
private:
	double m_lastUpdate = 0.0;
	std::vector<std::shared_ptr<SceneElement>> m_objects;
	std::shared_ptr<LightSourceElement> m_lightSource;
	std::shared_ptr<Window> m_window = nullptr;
	std::shared_ptr<CameraElement> m_camera = nullptr;
	void OnUpdate();
	void OnAwake();
	void RenderSceneElement(std::shared_ptr<SceneElement> ro);
};