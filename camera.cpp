#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "time.hpp"

glm::mat4 Camera::getView()
{
    return glm::lookAt(m_pos, m_pos + m_forward, m_up);
}

glm::mat4 Camera::getProjection(float aspect)
{
    return glm::perspective(glm::radians(m_fov), aspect, 0.1f, 100.0f);
}

void Camera::move(Move dir)
{
    glm::vec3 right = glm::normalize(glm::cross(m_up, m_forward));
    //glm::vec3 up = glm::normalize(glm::cross(right, m_forward))
    float step = Time::deltaTime * m_speed;

    switch (dir) {
    case Move::Forward:
        m_pos += m_forward * step;
        break;
    case Move::Back:
        m_pos -= m_forward * step;
        break;
    case Move::Right:
        m_pos += right * step;
        break;
    case Move::Left:
        m_pos -= right * step;
        break;
    case Move::Up:
        m_pos += m_up * step;
        break;
    case Move::Down:
        m_pos -= m_up * step;
    }
}

void Camera::look(glm::vec2 delta)
{
    m_yaw += delta.x;
    m_pitch += delta.y;
}
