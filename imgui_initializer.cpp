#include "imgui_initializer.hpp"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "window.hpp"
#include <memory>

/// <summary>
/// Initializes ImGui and connects it to the application window and OpenGL.
/// </summary>
/// <param name="window">
/// The application window used by ImGui.
/// </param>
void ImGuiInitializer::Initialize(std::shared_ptr<Window> window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window->GetGlfwWindowInstance(), true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

/// <summary>
/// Shuts down the ImGui backends and destroys the ImGui context.
/// </summary>
void ImGuiInitializer::Shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
