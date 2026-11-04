#include "engine.hpp"
#include <memory>
#include "window.hpp"
#include "light_source_element.hpp"
#include "camera_element.hpp"
#include "obj_loader.hpp"
#include "mesh.hpp"
#include "imgui_initializer.hpp"
#include "skybox_element.hpp"

/// <summary>
/// Creates the application objects, starts the engine, and shuts down ImGui.
/// </summary>
/// <returns>
/// Zero after the application exits successfully.
/// </returns>
int main() {

	auto window = std::make_shared<Window>(
		"Test",
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
		"C:/Users/huber/Documents/Programmieren/C++/Hauptprojekte/3D Model-Viewer/shaders/light/light.vert",
		"C:/Users/huber/Documents/Programmieren/C++/Hauptprojekte/3D Model-Viewer/shaders/light/light.frag"
	);

	lightSource->SetShader(lightSourceShader);
	lightSource->SetMesh(
		std::make_shared<Mesh>(
			loader.LoadFromOBJ(
				R"(C:\Users\huber\Documents\Programmieren\C++\Hauptprojekte\3D Model-Viewer\models\cube.obj)"
			)
		)
	);

	//CAMERA
	auto camera = std::make_shared<CameraElement>();

	//SKYBOX
	auto skybox = std::make_shared<SkyboxElement>(
		R"(C:\Users\huber\Documents\Programmieren\C++\Hauptprojekte\3D Model-Viewer\textures\cubemap\right.png)",
		R"(C:\Users\huber\Documents\Programmieren\C++\Hauptprojekte\3D Model-Viewer\textures\cubemap\left.png)",
		R"(C:\Users\huber\Documents\Programmieren\C++\Hauptprojekte\3D Model-Viewer\textures\cubemap\top.png)",
		R"(C:\Users\huber\Documents\Programmieren\C++\Hauptprojekte\3D Model-Viewer\textures\cubemap\bottom.png)",
		R"(C:\Users\huber\Documents\Programmieren\C++\Hauptprojekte\3D Model-Viewer\textures\cubemap\front.png)",
		R"(C:\Users\huber\Documents\Programmieren\C++\Hauptprojekte\3D Model-Viewer\textures\cubemap\back.png)"
	);

	auto skyboxShader = std::make_shared<Shader>(
		"C:/Users/huber/Documents/Programmieren/C++/Hauptprojekte/3D Model-Viewer/shaders/skybox/skybox.vert",
		"C:/Users/huber/Documents/Programmieren/C++/Hauptprojekte/3D Model-Viewer/shaders/skybox/skybox.frag"
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