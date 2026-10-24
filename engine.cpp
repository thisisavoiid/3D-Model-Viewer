#include "engine.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "time.h"
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
}

/// <summary>
/// Renders a single render object using its vertices, indices, and shader.
/// </summary>
/// <param name="ro">
/// The render object to draw.
/// </param>
void Engine::renderObject(std::shared_ptr<RenderObject> ro)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::vector<unsigned int> renderObjectIndices = ro->getIndices();
	std::vector<float> renderObjectVertices = ro->getVertices();

	unsigned vao, vbo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * renderObjectVertices.size(), renderObjectVertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int ebo;

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * renderObjectIndices.size(), renderObjectIndices.data(), GL_STATIC_DRAW);

	glEnable(GL_DEPTH_TEST);

	std::shared_ptr<Shader> shader = ro->getShader();

	glm::mat4 model(1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3));
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1, 1, -1));
	model = glm::scale(model, glm::vec3(0.5f));

	shader->setMat4("uModel", model);
	shader->setMat4("uView", view);
	shader->setMat4("uProj", proj);

	shader->use();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, renderObjectIndices.size(), GL_UNSIGNED_INT, 0);
}


/// <summary>
/// Starts the main engine loop.
/// </summary>
void Engine::run()
{
	auto glfwWindowInstance = m_window->getGlfwWindowInstance();

	m_lastUpdate = glfwGetTime();

	while (!glfwWindowShouldClose(glfwWindowInstance)) {
		onUpdate();

		for (const std::shared_ptr<RenderObject> renderObj : m_objects) {
			renderObj->beforeDraw();
			renderObject(renderObj);
		}

		glfwSwapBuffers(m_window->getGlfwWindowInstance());
		glfwPollEvents();
	}
}