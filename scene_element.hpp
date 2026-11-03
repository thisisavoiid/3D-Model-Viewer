#pragma once

#include "shader.hpp"
#include "time.hpp"
#include "texture.hpp"
#include <memory>
#include "mesh.hpp"
#include <glm/glm.hpp>
#include "transform.hpp"
#include "input.hpp"

class SceneElement {
public:
	void SetShader(std::shared_ptr<Shader> shader);
	void SetMesh(std::shared_ptr<Mesh> mesh);
	void SetTexture(std::shared_ptr<Texture> texture);

	/// <summary>
	/// Updates this render object each frame. Override in derived classes.
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// Called just before drawing this render object. Override in derived classes.
	/// </summary>
	virtual void BeforeDraw() = 0;

	virtual void Awake() = 0;

	Transform m_transform;

	std::shared_ptr<Shader> GetShader() const;
	std::shared_ptr<Mesh> GetMesh() const;
	std::shared_ptr<Texture> GetTexture() const;

	glm::mat4 GetModelMatrix() const;

	virtual ~SceneElement() = default;
private:
	std::shared_ptr<Shader> m_shader = nullptr;
	std::shared_ptr<Mesh> m_mesh = nullptr;
	std::shared_ptr<Texture> m_texture = nullptr;
};