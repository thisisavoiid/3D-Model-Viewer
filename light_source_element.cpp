#include "light_source_element.hpp"
#include "engine.hpp"
#include <iostream>
#include <glm/gtc/constants.hpp>

/// <summary>
/// Updates the light position and animated color for the current frame.
/// </summary>
void LightSourceElement::Update()
{
	m_transform.position.y = sin(Time::s_Time * 1.5f) * 2.0f;
	m_transform.position.x = cos(Time::s_Time * 0.5f) * 5.0f;
	m_transform.position.z = cos(Time::s_Time * 1.5f) * 2.0f;

	constexpr float shift = glm::two_pi<float>() / 3.0f;
	float t = Time::s_Time * 0.1f;

	m_lightColor = glm::vec3(
		sin(t) * 0.5f + 0.5f,
		sin(t + shift) * 0.5f + 0.5f,
		sin(t + shift * 2.0f) * 0.5f + 0.5f
	);
}

/// <summary>
/// Sets the light color uniform before drawing the light source.
/// </summary>
void LightSourceElement::BeforeDraw()
{
	std::shared_ptr<Shader> shader = GetShader();
	shader->SetVec3("uLightColor", m_lightColor);
}

/// <summary>
/// Initializes the light transform and registers the light with the engine.
/// </summary>
/// <param name="engine">
/// The engine that owns the scene.
/// </param>
void LightSourceElement::Awake(Engine& engine)
{
	m_transform.position += glm::vec3(2.0f, 0.0f, 0.0f);
	m_transform.scale *= glm::vec3(0.25f);

	engine.SetLightSource(shared_from_this());
}

/// <summary>
/// Constructs a light source with the specified initial color.
/// </summary>
/// <param name="color">
/// The initial light color.
/// </param>
LightSourceElement::LightSourceElement(glm::vec3 color)
{
	m_lightColor = color;
}

/// <summary>
/// Gets the current light position.
/// </summary>
/// <returns>
/// The light position.
/// </returns>
glm::vec3 LightSourceElement::GetLightPosition() const
{
	return m_transform.position;
}

/// <summary>
/// Gets the current light color.
/// </summary>
/// <returns>
/// The light color.
/// </returns>
glm::vec3 LightSourceElement::GetLightColor() const
{
	return m_lightColor;
}
