#include "cube_element.hpp"
#include "shader.hpp"
#include <memory>
#include <glm/glm.hpp>
#include "time.hpp"
#include <iostream>

void CubeElement::Awake() {
	Input::SetCursorMode(GLFW_CURSOR_DISABLED);
}

void CubeElement::BeforeDraw() {
	std::shared_ptr<Shader> shader = this->GetShader();
	shader->SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	shader->SetVec3("objectColor", glm::vec3(0.0f, 1.0f, 0.0f));
}

void CubeElement::Update() {
	m_transform.rotation.y += (m_speed * Time::s_DeltaTime) * Input::IsKeyHeld(Key::V);

	if (Input::IsKeyPressed(Key::MouseX2))
	{
		std::cout << "Speed increased. New speed: " << m_speed << "x\n";

		float target = m_speed + 0.5f;
		m_speed = glm::clamp(target, 1.0f, 10.0f);
	}

	if (Input::IsKeyPressed(Key::MouseX1)) {
		std::cout << "Speed decreased. New speed: " << m_speed << "x\n";

		float target = m_speed - 0.5f;
		m_speed = glm::clamp(target, 1.0f, 10.0f);
	}
}