#include "light_source_element.hpp"
#include "engine.hpp"

void LightSourceElement::Update()
{
	m_transform.position.y = sin(Time::s_Time * 1.5f) * 2.0f;
	m_transform.position.x = cos(Time::s_Time * 0.5f) * 5.0f;
	m_transform.position.z = cos(Time::s_Time * 1.5f) * 2.0f;

	//m_lightColor = glm::vec3(
	//	abs(sin(Time::s_Time)) * 1.0f,
	//	abs(cos(Time::s_Time)) * 1.0f,
	//	abs(sin(Time::s_Time)) * 1.0f
	//);
}

void LightSourceElement::BeforeDraw()
{

}

void LightSourceElement::Awake(Engine& engine)
{
	m_transform.position += glm::vec3(2.0f, 0.0f, 0.0f);
	m_transform.scale *= glm::vec3(0.25f);

	engine.SetLightSource(shared_from_this());
}

LightSourceElement::LightSourceElement(glm::vec3 color)
{
	m_lightColor = color;
}

glm::vec3 LightSourceElement::GetLightPosition() const
{
	return m_transform.position;
}

glm::vec3 LightSourceElement::GetLightColor() const
{
	return m_lightColor;
}
