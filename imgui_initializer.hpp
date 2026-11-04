#pragma once
#include "window.hpp"
#include <memory>

/// <summary>
/// Initializes and shuts down the ImGui context and its window integration.
/// </summary>
class ImGuiInitializer {
public:
	void Initialize(std::shared_ptr<Window> window);
	void Shutdown();
};