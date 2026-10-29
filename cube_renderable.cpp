#include "cube_renderable.hpp"
#include "shader.hpp"
#include <memory>
#include <glm/glm.hpp>
#include "time.hpp"

void CubeRenderable::beforeDraw() {
	//std::cout << "test\n";
	std::shared_ptr<Shader> shader = this->getShader();
	shader->setVec3("uColor", glm::vec3(1.0f, 0.0f, 1.0f));
}

void CubeRenderable::update() {
	m_transform.rotation.y += 0.5f * Time::deltaTime;
	m_transform.rotation.x -= 0.5f * Time::deltaTime;

	m_transform.position.y = sin(Time::time * 1.5f) * 0.5f;
	m_transform.position.x = cos(Time::time * 1.5f) * 0.5f;
}