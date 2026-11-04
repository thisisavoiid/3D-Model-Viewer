#include "gui_drawer.hpp"
#include <imgui.h>
#include <ImGuiFileDialog.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <iostream>

void GUIDrawer::PrepareNewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUIDrawer::BuildGUI(ImGuiIO& io)
{
    ImGui::Begin("Debug");

    if (ImGui::Button("Open File Dialog")) {
        IGFD::FileDialogConfig config;
        config.path = ".";
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".obj", config);
    }

    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
        if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            //std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            
            // ACTION HERE...
        }

        ImGuiFileDialog::Instance()->Close();
    }

    ImGui::Text("FPS: %.1f", io.Framerate);
    ImGui::End();
}

void GUIDrawer::RenderGUI()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
