#include "render_object.hpp"
#include "shader.hpp"
#include <memory>
#include <iostream>

void RenderObject::setShader(std::shared_ptr<Shader> shader)
{
	m_shader = shader;
}

void RenderObject::setMesh(std::shared_ptr<Mesh> mesh)
{
	m_mesh = mesh;
}

std::shared_ptr<Mesh> RenderObject::getMesh() {
	return m_mesh;
}

std::shared_ptr<Shader> RenderObject::getShader()
{
	return m_shader;
}


