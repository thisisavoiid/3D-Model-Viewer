#include <glad/glad.h>     
#include <GLFW/glfw3.h>    
#include "engine.hpp"
#include <memory>
#include <string>
#include "texture.hpp"
#include <filesystem>
#include <vector>
#include <utility>
#include "window.hpp"
#include "cube_element.hpp"
#include "light_source_element.hpp"
#include "camera_element.hpp"

int main() {
	auto window = std::make_shared<Window>(
		"Test",
		600,
		400
	);

	// CUBE
	std::vector<float> vertices = {
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
	};
	std::vector<unsigned int> indices = {
		// front and back
		0, 3, 2,
		2, 1, 0,
		4, 5, 6,
		6, 7 ,4,
		// left and right
		11, 8, 9,
		9, 10, 11,
		12, 13, 14,
		14, 15, 12,
		// bottom and top
		16, 17, 18,
		18, 19, 16,
		20, 21, 22,
		22, 23, 20
	};
	std::vector<float> normals = {
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,

		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,

		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,

		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,

		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,

		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f
	};
	std::vector<float> uvs = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	// Testtextur im Arbeitsverzeichnis unter assets/test_texture.png ablegen.
	const std::filesystem::path texturePath =
		std::filesystem::current_path() / "textures" / "test.jpg";
	const std::string texturePathString = texturePath.string();
	auto textureUnique = std::make_unique<Texture>(texturePathString.c_str());
	std::shared_ptr<Texture> texture = std::move(textureUnique);

	auto cube = std::make_shared<CubeElement>();
	cube->SetTexture(texture);
	auto cubeShader = std::make_shared<Shader>(
		"C:/Users/huber/Documents/Programmieren/C++/Hauptprojekte/3D Model-Viewer/shaders/cube/cube.vert", 
		"C:/Users/huber/Documents/Programmieren/C++/Hauptprojekte/3D Model-Viewer/shaders/cube/cube.frag"
	);
	auto mesh = std::make_shared<Mesh>(vertices, indices, normals, uvs);

	cube->SetMesh(mesh);
	cube->SetShader(cubeShader);

	//LIGHT SOURCE
	auto lightSource = std::make_shared<LightSourceElement>(
		glm::vec3(1.0f,1.0f,1.0f)
	);

	auto lightSourceShader = std::make_shared<Shader>(
		"C:/Users/huber/Documents/Programmieren/C++/Hauptprojekte/3D Model-Viewer/shaders/light/light.vert",
		"C:/Users/huber/Documents/Programmieren/C++/Hauptprojekte/3D Model-Viewer/shaders/light/light.frag"
	);

	lightSource->SetMesh(mesh);
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

	return 0;
}