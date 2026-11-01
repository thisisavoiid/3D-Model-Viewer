#include "engine.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "time.hpp"
#include "render_object.hpp"
#include "input.hpp"
#include "light_source_renderable.hpp"
/// <summary>
/// Loads a render object into the engine for rendering.
/// </summary>
/// <param name="ro">
/// The render object to add to the engine's object list.
/// </param>
void Engine::LoadObject(std::shared_ptr<RenderObject> ro)
{
	m_objects.push_back(ro);
	std::cout << "Added render object #" << m_objects.size() << "\n";
}

/// <summary>
/// Sets the window associated with this engine instance.
/// </summary>
/// <param name="window">
/// The window to use for rendering and event handling.
/// </param>
void Engine::SetWindow(std::shared_ptr<Window> window)
{
	m_window = window;
}

void Engine::SetCamera(std::shared_ptr<Camera> camera)
{
	m_camera = camera;
}

void Engine::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_camera->Move(MoveDir::Forward);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_camera->Move(MoveDir::Back);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m_camera->Move(MoveDir::Left);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m_camera->Move(MoveDir::Right);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		m_camera->Move(MoveDir::Up);

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		m_camera->Move(MoveDir::Down);
}

/// <summary>
/// Updates all loaded render objects and calculates delta time.
/// </summary>
void Engine::OnUpdate() {
	GLFWwindow* glfwWindowInstance = m_window->GetGlfwWindowInstance();

	double now = glfwGetTime();
	float deltaTime = static_cast<float>(now - m_lastUpdate);
	m_lastUpdate = now;
	Time::SetDeltaTime(deltaTime);

	Input::UpdateKeyInput();

	double xpos, ypos;
	glfwGetCursorPos(glfwWindowInstance, &xpos, &ypos);

	Input::UpdateCursorPosition(xpos, ypos);

	for (const std::shared_ptr<RenderObject> renderObj : m_objects) {
		if (renderObj == nullptr)
			continue;

		renderObj->Update();
	}

	ProcessInput(glfwWindowInstance); // TODO: Decouple Camera input
}

/// <summary>
/// Renders a single render object using its vertices, indices, and shader.
/// </summary>
/// <param name="ro">
/// The render object to draw.
/// </param>
void Engine::RenderSingleObject(std::shared_ptr<RenderObject> ro)
{
	if (ro == nullptr)
		return;

	std::shared_ptr<Shader> shader = ro->GetShader();
	std::shared_ptr<Mesh> mesh = ro->GetMesh();
	glm::mat4 model = ro->GetModelMatrix();

	if (shader != nullptr)
		shader->SetMat4("uModel", model);

	if (mesh != nullptr)
		ro->GetMesh()->Draw();
}

void Engine::OnAwake() {
	for (const std::shared_ptr<RenderObject> renderObj : m_objects) {
		if (renderObj == nullptr)
			continue;

		renderObj->Awake();
	}
}

/// <summary>
/// Starts the main engine loop.
/// </summary>
void Engine::Run()
{
	auto glfwWindowInstance = m_window->GetGlfwWindowInstance();
	m_lastUpdate = glfwGetTime();
	glEnable(GL_DEPTH_TEST);

	OnAwake();

	glm::vec3 lightPos(0.0f);
	glm::vec3 lightCol(1.0f);

	while (!glfwWindowShouldClose(glfwWindowInstance)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int width, height;
		glfwGetFramebufferSize(glfwWindowInstance, &width, &height);

		float aspect = (height > 0) ? (float)width / height : 1.0f;

		glm::mat4 view = m_camera->GetView();
		glm::mat4 projection = m_camera->GetProjection(aspect);

		for (auto& obj : m_objects) {
			if (obj == nullptr)
				continue;

			//TODO: Refactor light source fetching!
			if (auto light = std::dynamic_pointer_cast<LightSourceRenderable>(obj)) {
				lightPos = light->GetLightPosition();
				lightCol = light->GetLightColor();
			}

			//std::cout << lightPos.x << "|" << lightPos.y << "|" << lightPos.z << "\n";

			std::shared_ptr<Texture> texture = obj->GetTexture();
			std::shared_ptr<Shader> shader = obj->GetShader();

			if (texture != nullptr)
			{
				texture->Use();

				if (shader != nullptr)
				{
					shader->SetInt("uTexture", 0);
				}
			}

			if (shader != nullptr)
			{
				shader->Use();
				shader->SetMat4("uView", view);
				shader->SetMat4("uProj", projection);

				shader->SetVec3("lightPos", lightPos);
			}

			obj->BeforeDraw();

			RenderSingleObject(obj);
		}

		OnUpdate();

		// TODO!!
		glm::vec2 cursorDelta = Input::GetCursorDelta();
		m_camera->Look(cursorDelta);

		glfwSwapBuffers(m_window->GetGlfwWindowInstance());
		glfwPollEvents();
	}
}