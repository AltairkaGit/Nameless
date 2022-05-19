#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Core/context.h"

class OpenGLContext : public Context
{
public:
	OpenGLContext(GLFWwindow* window);

	virtual void init() override;
	virtual void swapBuffers() override;
private:
	GLFWwindow* m_Window;
};