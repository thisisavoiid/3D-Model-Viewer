#pragma once
#include <glm/glm.hpp>

enum class Move {
	Forward, Back, Left, Right, Up, Down
};

class Camera {
public:
	glm::mat4 getView();
	glm::mat4 getProjection(float aspect);
	void move(Move dir);
	void look(glm::vec2 delta);
private:
	glm::vec3 m_pos{ 0.0f,0.0f,3.0f };
	glm::vec3 m_forward{ 0.0f,0.0f,-1.0f };
	glm::vec3 m_up{ 0.0f,1.0f,0.0f };
	float m_yaw; // Left & Right
	float m_pitch; // Up & Down
	float m_fov = 45.0f;
	float m_speed = 5.0f;
};