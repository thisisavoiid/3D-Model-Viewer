#include "light_source_renderable.hpp"

void LightSourceRenderable::Update()
{
	m_transform.position.y = sin(Time::s_Time * 1.5f) * 2.0f;
	m_transform.position.x = cos(Time::s_Time * 0.5f) * 5.0f;
	m_transform.position.z = cos(Time::s_Time * 1.5f) * 2.0f;
}

void LightSourceRenderable::BeforeDraw()
{

}

void LightSourceRenderable::Awake()
{
	m_transform.position += glm::vec3(2.0f, 0.0f, 0.0f);
	m_transform.scale *= glm::vec3(0.25f);
}

glm::vec3 LightSourceRenderable::GetLightPosition() const
{
	return m_transform.position;
}

glm::vec3 LightSourceRenderable::GetLightColor() const
{
	return m_lightColor;
}
