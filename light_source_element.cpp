#include "light_source_element.hpp"

void LightSourceElement::Update()
{
	m_transform.position.y = sin(Time::s_Time * 1.5f) * 2.0f;
	m_transform.position.x = cos(Time::s_Time * 0.5f) * 5.0f;
	m_transform.position.z = cos(Time::s_Time * 1.5f) * 2.0f;
}

void LightSourceElement::BeforeDraw()
{

}

void LightSourceElement::Awake()
{
	m_transform.position += glm::vec3(2.0f, 0.0f, 0.0f);
	m_transform.scale *= glm::vec3(0.25f);
}

glm::vec3 LightSourceElement::GetLightPosition() const
{
	return m_transform.position;
}

glm::vec3 LightSourceElement::GetLightColor() const
{
	return m_lightColor;
}
