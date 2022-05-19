#include <GLFW/glfw3.h>
#include "Core/renderer.h"
#include "Core/input.h"

bool Input::isKeyPressed(KeyCode key)
{
	GLFWwindow* window = reinterpret_cast<GLFWwindow*>(Renderer::getWindow());
	int state = glfwGetKey(window, static_cast<int32_t>(key));
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::isMousePressed(MouseCode button)
{
	GLFWwindow* window = reinterpret_cast<GLFWwindow*>(Renderer::getWindow());
	int state = glfwGetKey(window, static_cast<int32_t>(button));
}