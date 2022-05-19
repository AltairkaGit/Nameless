#include "OpenGLContext.h"

OpenGLContext::OpenGLContext(GLFWwindow* window)
	: m_Window(window)
{
}

void OpenGLContext::init()
{
	glfwMakeContextCurrent(m_Window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to intiialize GLAD" << std::endl;
		return;
	}
}

void OpenGLContext::swapBuffers()
{
	glfwSwapBuffers(m_Window);
}