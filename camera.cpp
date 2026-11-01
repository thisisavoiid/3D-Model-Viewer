#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "time.hpp"

glm::mat4 Camera::GetView() const
{
    return glm::lookAt(m_pos, m_pos + m_forward, m_up);
}

glm::mat4 Camera::GetProjection(float aspect) const
{
    return glm::perspective(glm::radians(m_fov), aspect, 0.1f, 100.0f);
}

glm::vec3 Camera::GetPosition() const
{
    return m_pos;
}

void Camera::Move(MoveDir dir)
{
    glm::vec3 right = glm::normalize(glm::cross(m_up, m_forward));
    //glm::vec3 up = glm::normalize(glm::cross(right, m_forward))
    float step = Time::s_DeltaTime * m_speed;

    switch (dir) {
    case MoveDir::Forward:
        m_pos += m_forward * step;
        break;
    case MoveDir::Back:
        m_pos -= m_forward * step;
        break;
    case MoveDir::Right:
        m_pos += right * step;
        break;
    case MoveDir::Left:
        m_pos -= right * step;
        break;
    case MoveDir::Up:
        m_pos += m_up * step;
        break;
    case MoveDir::Down:
        m_pos -= m_up * step;
    }
}

void Camera::Look(glm::vec2 delta)
{
    m_yaw += delta.x * m_sens;
    m_pitch += delta.y * -1 * m_sens;

    m_pitch = glm::clamp(m_pitch, -89.0f, 89.0f);

    glm::vec3 modifiedForward;

    modifiedForward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    modifiedForward.y = sin(glm::radians(m_pitch));
    modifiedForward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_forward = glm::normalize(modifiedForward);
}
