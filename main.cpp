#include <glad/glad.h>     
#include <GLFW/glfw3.h>    
#include "engine.hpp"
#include <memory>
#include <string>
#include <filesystem>
#include <vector>
#include "window.hpp"

int main() {
	auto cube = std::make_shared<RenderObject>();

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

	cube->setVertices(vertices);
	cube->setIndices(indices);

	auto window = std::make_shared<Window>(
		"Test",
		600,
		400
	);

	const std::filesystem::path shaderDirectory = "shaders/test";
	const std::string vertexPath =
		(shaderDirectory / "test.vert").string();
	const std::string fragmentPath =
		(shaderDirectory / "test.frag").string();

	Shader shader(vertexPath.c_str(), fragmentPath.c_str());

	cube->setShader(std::make_shared<Shader>(shader));

    Engine engine;
	engine.setWindow(window);
    engine.loadObject(cube);
	engine.run();

  


    //engine.start();

    //delete(cube);
    //cube = nullptr;

    return 0;
}