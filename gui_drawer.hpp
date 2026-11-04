#pragma once

#include <imgui.h>
#include <filesystem>
#include <optional>
#include "model_import_selection.hpp"

/// <summary>
/// Builds and renders the application's graphical user interface.
/// </summary>
class GUIDrawer {
public:
	static void PrepareNewFrame();
	static void BuildGUI(ImGuiIO& io);
	static void RenderGUI();
	static std::optional<ModelImportSelection> ConsumeLoadRequestData();
private:
	static inline std::optional<std::filesystem::path> m_objPathSelected;
	static inline std::optional<std::filesystem::path> m_vertPathSelected;
	static inline std::optional<std::filesystem::path> m_fragPathSelected;
	static inline std::optional<std::filesystem::path> m_texturePathSelected;
	static inline std::optional<ModelImportSelection> m_loadRequestData;
	static void DrawFileDialogs();
};