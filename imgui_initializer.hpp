#pragma once
#include "window.hpp"
#include <memory>

class ImGuiInitializer {
public:
	void Initialize(std::shared_ptr<Window> window);
	void Shutdown();
};