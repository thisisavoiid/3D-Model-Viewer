#include "engine.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include "time.hpp"
#include "scene_element.hpp"
#include "input.hpp"
#include "light_source_element.hpp"
#include "camera_element.hpp"
#include <string>
#include <format>
#include <imgui.h>
#include "gui_drawer.hpp"
#include "obj_loader.hpp"
#include "demo_element.hpp"
#include "model_import_selection.hpp"

/// <summary>
/// Loads a render object into the engine for rendering.
/// </summary>
/// <param name="ro">
/// The render object to add to the engine's object list.
/// </param>
void Engine::LoadObject(std::shared_ptr<SceneElement> sceneElem)
{
	if (sceneElem == nullptr)
		return;

	m_objects.push_back(sceneElem);
	std::cout << std::format("Added scene element #{} -\n", m_objects.size());
}

/// <summary>
/// Sets the window associated with this engine instance.
/// </summary>
/// <param name="window">
/// The window to use for rendering and event handling.
/// </param>
void Engine::SetWindow(std::shared_ptr<Window> window)
{
	if (window == nullptr)
		return;

	m_window = window;
}

/// <summary>
/// Sets the camera used for rendering the scene.
/// </summary>
/// <param name="camera">
/// The camera to use for rendering.
/// </param>
void Engine::SetCamera(std::shared_ptr<CameraElement> camera)
{
	m_camera = camera;
}

/// <summary>
/// Sets the light source used when rendering scene elements.
/// </summary>
/// <param name="source">
/// The light source to use for rendering.
/// </param>
void Engine::SetLightSource(std::shared_ptr<LightSourceElement> source)
{
	if (source == nullptr)
		return;

	m_lightSource = source;
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

	int currentCursorMode = Input::GetCursorMode();

	if (currentCursorMode == GLFW_CURSOR_DISABLED)
		Input::UpdateCursorPosition(xpos, ypos);

	if (Input::IsKeyPressed(Key::Escape)) {

		int width, height;
		glfwGetWindowSize(glfwWindowInstance, &width, &height);

		Input::SetCursorPosition(width / 2.0, height / 2.0);

		if (currentCursorMode == GLFW_CURSOR_DISABLED)
			Input::SetCursorMode(GLFW_CURSOR_NORMAL);
		else if (currentCursorMode == GLFW_CURSOR_NORMAL)
			Input::SetCursorMode(GLFW_CURSOR_DISABLED);
	}

	for (const std::shared_ptr<SceneElement> sceneElem : m_objects) {
		if (sceneElem == nullptr)
			continue;

		sceneElem->Update();
	}
}

/// <summary>
/// Renders a single render object using its vertices, indices, and shader.
/// </summary>
/// <param name="ro">
/// The render object to draw.
/// </param>
void Engine::RenderSceneElement(std::shared_ptr<SceneElement> ro)
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

/// <summary>
/// Invokes the initialization callback for every loaded scene element.
/// </summary>
void Engine::OnAwake() {
	for (const std::shared_ptr<SceneElement> sceneElem : m_objects) {
		if (sceneElem == nullptr)
			continue;

		sceneElem->Awake(*this);
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

	ImGuiIO& io = ImGui::GetIO();
	ObjLoader loader;

	OnAwake();

	glm::vec3 lightPos(0.0f);
	glm::vec3 lightCol(1.0f);

	while (!glfwWindowShouldClose(glfwWindowInstance)) {
		GUIDrawer::PrepareNewFrame();
		GUIDrawer::BuildGUI(io);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int width, height;
		glfwGetFramebufferSize(glfwWindowInstance, &width, &height);

		float aspect = (height > 0) ? (float)width / height : 1.0f;

		glm::mat4 view = m_camera != nullptr ? m_camera->GetView() : glm::mat4(1.0f);
		glm::mat4 projection = m_camera != nullptr ? m_camera->GetProjection(aspect) : glm::mat4(1.0f);

		for (auto& obj : m_objects) {
			if (obj == nullptr)
				continue;

			if (m_lightSource != nullptr) {
				lightPos = m_lightSource->GetLightPosition();
				lightCol = m_lightSource->GetLightColor();
			}

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
				shader->SetMat4("uView", obj->GetViewMatrix(view));
				shader->SetMat4("uProj", projection);

				if (m_lightSource != nullptr) {
					shader->SetVec3("uLightPos", lightPos);
					shader->SetVec3("uLightColor", lightCol);
				}

				if (m_camera != nullptr)
				{
					shader->SetVec3("uViewPos", m_camera->m_transform.position);
				}
			}

			obj->BeforeDraw();

			RenderSceneElement(obj);

			obj->AfterDraw();
		}

		OnUpdate();

		GUIDrawer::RenderGUI();

		if (std::optional<ModelImportSelection> importData = GUIDrawer::ConsumeLoadRequestData())
		{
			MeshData meshData = loader.LoadFromOBJ(importData->objPath);

			std::shared_ptr<Shader> shaderPtr = std::make_shared<Shader>(importData->vertPath, importData->fragPath);
			std::shared_ptr<Mesh> meshPtr = std::make_shared<Mesh>(meshData);
			std::shared_ptr<Texture> texturePtr = std::make_shared<Texture>(importData->texturePath);

			std::shared_ptr<DemoElement> demoSceneElem = std::make_shared<DemoElement>();

			demoSceneElem->SetMesh(meshPtr);
			demoSceneElem->SetShader(shaderPtr);
			demoSceneElem->SetTexture(texturePtr);

			LoadObject(demoSceneElem);
		}

		glfwSwapBuffers(m_window->GetGlfwWindowInstance());
		glfwPollEvents();
	}
}