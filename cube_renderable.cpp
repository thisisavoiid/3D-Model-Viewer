#include "cube_renderable.hpp"
#include "shader.hpp"
#include <memory>
#include <glm/glm.hpp>
#include "time.hpp"
#include <iostream>

float speed = 1.0f;

void CubeRenderable::awake() {
	Input::SetCursorMode(GLFW_CURSOR_DISABLED);
}

void CubeRenderable::beforeDraw() {
	std::shared_ptr<Shader> shader = this->getShader();
	shader->setVec3("uColor", glm::vec3(1.0f, 0.0f, 1.0f));
}

void CubeRenderable::update() {
	m_transform.rotation.y += (speed * Time::deltaTime) * Input::IsKeyHeld(Key::V);

	if (Input::IsKeyPressed(Key::MouseX2))
	{
		std::cout << "Speed increased. New speed: " << speed << "x\n";

		float target = speed + 0.5f;
		speed = glm::clamp(target, 1.0f, 10.0f);
	}

	if (Input::IsKeyPressed(Key::MouseX1)) {
		std::cout << "Speed decreased. New speed: " << speed << "x\n";

		float target = speed - 0.5f;
		speed = glm::clamp(target, 1.0f, 10.0f);
	}
}