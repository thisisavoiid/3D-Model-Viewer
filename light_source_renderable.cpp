#include "light_source_renderable.hpp"

void LightSourceRenderable::Update()
{
}

void LightSourceRenderable::BeforeDraw()
{

}

void LightSourceRenderable::Awake()
{
	m_transform.position += glm::vec3(5.0f, 0.0f, 0.0f);
	m_transform.scale *= glm::vec3(0.25f);
}
