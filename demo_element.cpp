#include "demo_element.hpp"
#include "shader.hpp"
#include <memory>
#include <glm/glm.hpp>
#include "time.hpp"
#include <iostream>
#include "input.hpp"
#include <string>
#include <format>

/// <summary>
/// Initializes the demo element when it is added to the scene.
/// </summary>
/// <param name="engine">
/// The engine that owns the scene.
/// </param>
void DemoElement::Awake(Engine& engine) {
}

/// <summary>
/// Sets the object color before drawing the demo element.
/// </summary>
void DemoElement::BeforeDraw() {
	std::shared_ptr<Shader> shader = this->GetShader();
	shader->SetVec3("uObjectColor", glm::vec3(1.0f, 1.0f, 1.0f));
}

/// <summary>
/// Rotates the demo element and handles speed input for the current frame.
/// </summary>
void DemoElement::Update() {
	m_transform.rotation.y += (m_speed * Time::s_DeltaTime) * Input::IsKeyHeld(Key::V);

	if (Input::IsKeyPressed(Key::MouseX2))
	{
		std::cout << std::format("Speed increased. New speed: {}\n", m_speed);

		float target = m_speed + 0.5f;
		m_speed = glm::clamp(target, 1.0f, 10.0f);
	}

	if (Input::IsKeyPressed(Key::MouseX1)) {
		std::cout << std::format("Speed decreased. New speed: {}\n", m_speed);

		float target = m_speed - 0.5f;
		m_speed = glm::clamp(target, 1.0f, 10.0f);
	}
}
