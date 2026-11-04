#include "engine.hpp"
#include <memory>
#include "texture.hpp"
#include "window.hpp"
#include "cube_element.hpp"
#include "light_source_element.hpp"
#include "camera_element.hpp"
#include "obj_loader.hpp"
#include "mesh.hpp"
#include "imgui_initializer.hpp"

int main() {

	auto window = std::make_shared<Window>(
		"Test",
		1200,
		900
	);

	ImGuiInitializer imgui;
	imgui.Initialize(window);

	std::filesystem::path objPath = R"(C:\Users\huber\Downloads\Cube OBJ\cube.obj)";

	ObjLoader objLoader;
	MeshData transformedObjMeshData = objLoader.LoadFromOBJ(objPath);

	std::shared_ptr<Mesh> objCubeMesh = std::make_shared<Mesh>(transformedObjMeshData);

	auto cube = std::make_shared<CubeElement>();

	auto cubeShader = std::make_shared<Shader>(
		"C:/Users/huber/Documents/Programmieren/C++/Hauptprojekte/3D Model-Viewer/shaders/cube/cube.vert",
		"C:/Users/huber/Documents/Programmieren/C++/Hauptprojekte/3D Model-Viewer/shaders/cube/cube.frag"
	);

	auto cubeTexture = std::make_shared<Texture>(
		"C:/Users/huber/Documents/Programmieren/C++/Hauptprojekte/3D Model-Viewer/textures/example_texture_01.png"
	);

	cube->SetMesh(objCubeMesh);
	cube->SetTexture(cubeTexture);
	cube->SetShader(cubeShader);

	//LIGHT SOURCE
	auto lightSource = std::make_shared<LightSourceElement>(
		glm::vec3(1.0f, 1.0f, 1.0f)
	);

	auto lightSourceShader = std::make_shared<Shader>(
		"C:/Users/huber/Documents/Programmieren/C++/Hauptprojekte/3D Model-Viewer/shaders/light/light.vert",
		"C:/Users/huber/Documents/Programmieren/C++/Hauptprojekte/3D Model-Viewer/shaders/light/light.frag"
	);

	lightSource->SetMesh(objCubeMesh);
	lightSource->SetShader(lightSourceShader);

	//CAMERA
	auto camera = std::make_shared<CameraElement>();

	//ENGINE
	Engine engine;
	engine.SetWindow(window);
	engine.LoadObject(cube);
	engine.LoadObject(camera);
	engine.LoadObject(lightSource);
	engine.Run();

	imgui.Shutdown();

	return 0;

}