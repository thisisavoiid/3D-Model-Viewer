#pragma once
#include <glm/glm.hpp>
#include "scene_element.hpp"

enum class MoveDir {
	Forward, Back, Left, Right, Up, Down
};

class CameraElement : public SceneElement, public std::enable_shared_from_this<CameraElement>{
public:
	glm::mat4 GetView() const;
	glm::mat4 GetProjection(float aspect) const;
	glm::vec3 GetPosition() const;

	void Look(glm::vec2 delta);

	void Update() override;
	void Awake(Engine& engine) override;
	void BeforeDraw() override;

private:
	glm::vec3 m_pos{ 0.0f,0.0f,3.0f };
	glm::vec3 m_forward{ 0.0f,0.0f,-1.0f };
	glm::vec3 m_up{ 0.0f,1.0f,0.0f };
	float m_yaw = -45.0f; // Left & Right
	float m_pitch = 0.0f; // Up & Down
	float m_fov = 45.0f;
	float m_speed = 5.0f;
	float m_sens = 0.075f;
};