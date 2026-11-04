#include "gui_drawer.hpp"
#include <imgui.h>
#include <ImGuiFileDialog.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <optional>
#include "model_import_selection.hpp"

void GUIDrawer::PrepareNewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void GUIDrawer::BuildGUI(ImGuiIO& io)
{
	ImGui::Begin("Debug");

	if (ImGui::Button("Select .OBJ")) {
		IGFD::FileDialogConfig config;
		config.path = ".";
		ImGuiFileDialog::Instance()->OpenDialog("ChooseObjKey", "Choose .OBJ File", ".obj", config);
	}

	ImGui::TextColored(
		!m_objPathSelected.has_value() ? ImColor(1.0f, 0.0f, 0.0f) : ImColor(0.0f, 1.0f, 0.0f),
		!m_objPathSelected.has_value() ? "No OBJ File Selected!" : m_objPathSelected->filename().string().c_str()
	);

	if (ImGui::Button("Select Vertex Shader")) {
		IGFD::FileDialogConfig config;
		config.path = ".";
		ImGuiFileDialog::Instance()->OpenDialog("ChooseVertKey", "Choose Vertex Shader File", ".vert", config);
	}

	ImGui::TextColored(
		!m_vertPathSelected.has_value() ? ImColor(1.0f, 0.0f, 0.0f) : ImColor(0.0f, 1.0f, 0.0f),
		!m_vertPathSelected.has_value() ? "No Vertex Shader File Selected!" : m_vertPathSelected->filename().string().c_str()
	);

	if (ImGui::Button("Select Fragment Shader")) {
		IGFD::FileDialogConfig config;
		config.path = ".";
		ImGuiFileDialog::Instance()->OpenDialog("ChooseFragKey", "Choose Fragment Shader File", ".frag", config);
	}

	ImGui::TextColored(
		!m_fragPathSelected.has_value() ? ImColor(1.0f, 0.0f, 0.0f) : ImColor(0.0f, 1.0f, 0.0f),
		!m_fragPathSelected.has_value() ? "No Fragment Shader File Selected!" : m_fragPathSelected->filename().string().c_str()
	);

	if (ImGui::Button("Select Texture")) {
		IGFD::FileDialogConfig config;
		config.path = ".";
		ImGuiFileDialog::Instance()->OpenDialog("ChooseTextureKey", "Choose Texture File", ".jpg,.png,.jpeg", config);
	}

	ImGui::TextColored(
		!m_texturePathSelected.has_value() ? ImColor(1.0f, 0.0f, 0.0f) : ImColor(0.0f, 1.0f, 0.0f),
		!m_texturePathSelected.has_value() ? "No Texture File Selected!" : m_texturePathSelected->filename().string().c_str()
	);

	DrawFileDialogs();

	ImGui::Separator();

	bool isEverythingSelected = m_objPathSelected.has_value() &&
								m_fragPathSelected.has_value() &&
								m_vertPathSelected.has_value() &&
								m_texturePathSelected.has_value();

	bool isImportDataOccupied = m_loadRequestData.has_value();

	ImGui::BeginDisabled(!isEverythingSelected || isImportDataOccupied);

	if (ImGui::Button("Import Model")) {
		m_loadRequestData = ModelImportSelection{
			*m_objPathSelected,
			*m_vertPathSelected,
			*m_fragPathSelected,
			*m_texturePathSelected
		};
	}

	ImGui::EndDisabled();

	ImGui::End();
}

void GUIDrawer::RenderGUI()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

std::optional<ModelImportSelection> GUIDrawer::ConsumeLoadRequestData()
{
	std::optional<ModelImportSelection> request = m_loadRequestData;

	if (m_loadRequestData.has_value()) {
		m_objPathSelected.reset();
		m_vertPathSelected.reset();
		m_fragPathSelected.reset();
		m_texturePathSelected.reset();
	}

	m_loadRequestData.reset();

	return request;
}

void GUIDrawer::DrawFileDialogs()
{
	IGFD::FileDialog* context = ImGuiFileDialog::Instance();

	if (context->Display("ChooseObjKey")) {
		if (context->IsOk()) {
			m_objPathSelected = context->GetFilePathName();
		}
		context->Close();
	}
	else if (context->Display("ChooseVertKey")) {
		if (context->IsOk()) {
			m_vertPathSelected = context->GetFilePathName();
		}

		context->Close();
	}
	else if (context->Display("ChooseFragKey")) {
		if (context->IsOk()) {
			m_fragPathSelected = context->GetFilePathName();
		}
		context->Close();
	}
	else if (context->Display("ChooseTextureKey")) {
		if (context->IsOk()) {
			m_texturePathSelected = context->GetFilePathName();
		}
		context->Close();
	}
}