#include "camera_element.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "time.hpp"
#include "engine.hpp"
#include "input.hpp"

/// <summary>
/// Calculates the view matrix from the camera's position and orientation.
/// </summary>
/// <returns>
/// The camera view matrix.
/// </returns>
glm::mat4 CameraElement::GetView() const
{
    return glm::lookAt(m_transform.position, m_transform.position + m_forward, m_up);
}

/// <summary>
/// Calculates the perspective projection matrix for the specified aspect ratio.
/// </summary>
/// <param name="aspect">
/// The viewport aspect ratio.
/// </param>
/// <returns>
/// The camera projection matrix.
/// </returns>
glm::mat4 CameraElement::GetProjection(float aspect) const
{
    return glm::perspective(glm::radians(m_fov), aspect, 0.1f, 100.0f);
}

/// <summary>
/// Gets the current camera position.
/// </summary>
/// <returns>
/// The camera position.
/// </returns>
glm::vec3 CameraElement::GetPosition() const
{
    return m_transform.position;
}

/// <summary>
/// Updates the camera orientation using cursor movement.
/// </summary>
/// <param name="delta">
/// The cursor movement since the previous update.
/// </param>
void CameraElement::Look(glm::vec2 delta)
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

/// <summary>
/// Updates the camera orientation and movement for the current frame.
/// </summary>
void CameraElement::Update()
{
    Look(Input::GetCursorDelta());

    glm::vec3 right = glm::normalize(glm::cross(m_up, m_forward));
    float step = Time::s_DeltaTime * m_speed;

    if (Input::IsKeyHeld(Key::A))
        m_transform.position += right * step;

    if (Input::IsKeyHeld(Key::D))
        m_transform.position += -right * step;

    if (Input::IsKeyHeld(Key::W))
        m_transform.position += m_forward * step;

    if (Input::IsKeyHeld(Key::S))
        m_transform.position += -m_forward * step;

    if (Input::IsKeyHeld(Key::Space) || Input::IsKeyHeld(Key::E))
        m_transform.position += m_up * step;

    if (Input::IsKeyHeld(Key::LeftShift) || Input::IsKeyHeld(Key::Q))
        m_transform.position += -m_up * step;
}

/// <summary>
/// Registers this camera with the engine during scene initialization.
/// </summary>
/// <param name="engine">
/// The engine that owns the scene.
/// </param>
void CameraElement::Awake(Engine& engine)
{
    engine.SetCamera(shared_from_this());
}

/// <summary>
/// Performs camera-specific preparation before drawing.
/// </summary>
void CameraElement::BeforeDraw()
{
}
