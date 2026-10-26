#include "engine.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "time.hpp"
#include "render_object.hpp"

/// <summary>
/// Loads a render object into the engine for rendering.
/// </summary>
/// <param name="ro">
/// The render object to add to the engine's object list.
/// </param>
void Engine::loadObject(std::shared_ptr<RenderObject> ro)
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
void Engine::setWindow(std::shared_ptr<Window> window)
{
	m_window = window;
}

void Engine::setCamera(std::shared_ptr<Camera> camera)
{
	m_camera = camera;
}

void Engine::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_camera->move(Move::Forward);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_camera->move(Move::Back);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m_camera->move(Move::Left);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m_camera->move(Move::Right);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		m_camera->move(Move::Up);

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		m_camera->move(Move::Down);
}

/// <summary>
/// Updates all loaded render objects and calculates delta time.
/// </summary>
void Engine::onUpdate() {
	double now = glfwGetTime();
	float deltaTime = static_cast<float>(now - m_lastUpdate);
	m_lastUpdate = now;
	Time::setDeltaTime(deltaTime);

	for (const std::shared_ptr<RenderObject> renderObj : m_objects) {
		renderObj->update();
	}

	processInput(m_window->getGlfwWindowInstance());
}

/// <summary>
/// Renders a single render object using its vertices, indices, and shader.
/// </summary>
/// <param name="ro">
/// The render object to draw.
/// </param>
void Engine::renderObject(std::shared_ptr<RenderObject> ro)
{
	std::vector<unsigned int> renderObjectIndices = ro->getMesh()->getIndices();
	std::vector<float> renderObjectVertices = ro->getMesh()->getVertices();

	std::shared_ptr<Shader> shader = ro->getShader();

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1, 1, -1));
	model = glm::scale(model, glm::vec3(0.5f));
	shader->setMat4("uModel", model);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ro->getMesh()->getEboBuffer());
	glDrawElements(GL_TRIANGLES, renderObjectIndices.size(), GL_UNSIGNED_INT, 0);
}


/// <summary>
/// Starts the main engine loop.
/// </summary>
void Engine::run()
{
	auto glfwWindowInstance = m_window->getGlfwWindowInstance();

	m_lastUpdate = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(glfwWindowInstance)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int width, height;
		glfwGetFramebufferSize(glfwWindowInstance, &width, &height);

		float aspect = (height > 0) ? (float)width / height : 1.0f;

		glm::mat4 view = m_camera->getView();
		glm::mat4 projection = m_camera->getProjection(aspect);

		for (auto& obj : m_objects) {
			obj->getShader()->use();
			obj->getShader()->setMat4("uView", view);
			obj->getShader()->setMat4("uProj", projection);
			obj->beforeDraw();
			renderObject(obj);
		}

		onUpdate();

		glfwSwapBuffers(m_window->getGlfwWindowInstance());
		glfwPollEvents();
	}
}