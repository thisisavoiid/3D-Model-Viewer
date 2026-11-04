#include "engine.hpp"
#include <memory>
#include "window.hpp"
#include "light_source_element.hpp"
#include "camera_element.hpp"
#include "obj_loader.hpp"
#include "mesh.hpp"
#include "imgui_initializer.hpp"

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
	
	ObjLoader loader;

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

	//ENGINE
	Engine engine;
	engine.SetWindow(window);
	engine.LoadObject(camera);
	engine.LoadObject(lightSource);
	engine.Run();

	imgui.Shutdown();

	return 0;

}