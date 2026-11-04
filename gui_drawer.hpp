#pragma once

#include <imgui.h>

class GUIDrawer {
public:
	static void PrepareNewFrame();
	static void BuildGUI(ImGuiIO& io);
	static void RenderGUI();
};