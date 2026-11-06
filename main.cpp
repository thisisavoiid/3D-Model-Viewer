#include "engine.hpp"
#include <memory>
#include "window.hpp"
#include "light_source_element.hpp"
#include "camera_element.hpp"
#include "obj_loader.hpp"
#include "mesh.hpp"
#include "imgui_initializer.hpp"
#include "skybox_element.hpp"
#include <filesystem>

const std::filesystem::path SHADER_DIR = "shaders";
const std::filesystem::path TEXTURE_DIR = "textures";
const std::filesystem::path MODELS_DIR = "models";

/// <summary>
/// Creates the application objects, starts the engine, and shuts down ImGui.
/// </summary>
/// <returns>
/// Zero after the application exits successfully.
/// </returns>
int main() {

	auto window = std::make_shared<Window>(
		"3D Model Viewer - Made by AVØIID",
		1200,
		900
	);

	ObjLoader loader;

	ImGuiInitializer imgui;
	imgui.Initialize(window);

	//LIGHT SOURCE
	auto lightSource = std::make_shared<LightSourceElement>(
		glm::vec3(1.0f, 1.0f, 1.0f)
	);

	auto lightSourceShader = std::make_shared<Shader>(
		(SHADER_DIR / "light/light.vert"),
		(SHADER_DIR / "light/light.frag")
	);

	lightSource->SetShader(lightSourceShader);
	lightSource->SetMesh(
		std::make_shared<Mesh>(
			loader.LoadFromOBJ(
				(MODELS_DIR / "cube.obj")
			)
		)
	);

	//CAMERA
	auto camera = std::make_shared<CameraElement>();

	//SKYBOX
	auto skybox = std::make_shared<SkyboxElement>(
		(TEXTURE_DIR / "cubemap/right.png"),
		(TEXTURE_DIR / "cubemap/left.png"),
		(TEXTURE_DIR / "cubemap/top.png"),
		(TEXTURE_DIR / "cubemap/bottom.png"),
		(TEXTURE_DIR / "cubemap/front.png"),
		(TEXTURE_DIR / "cubemap/back.png")
	);

	auto skyboxShader = std::make_shared<Shader>(
		(SHADER_DIR / "skybox/skybox.vert"),
		(SHADER_DIR / "skybox/skybox.frag")
	);

	skybox->SetShader(skyboxShader);

	//ENGINE
	Engine engine;
	engine.SetWindow(window);
	engine.LoadObject(skybox);
	engine.LoadObject(camera);
	engine.LoadObject(lightSource);
	engine.Run();

	imgui.Shutdown();

	return 0;
}