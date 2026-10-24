#include "cube_renderable.hpp"
#include "shader.hpp"
#include <memory>
#include <glm/glm.hpp>

void CubeRenderable::beforeDraw() {
	std::shared_ptr<Shader> shader = this->getShader();
	shader->setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));
}