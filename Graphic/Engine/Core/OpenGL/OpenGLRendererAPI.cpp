#include "OpenGLRendererAPI.h"

OpenGLRendererAPI::OpenGLRendererAPI()
{
	init();
}

void OpenGLRendererAPI::init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	stbi_set_flip_vertically_on_load(true);

	glEnable(GL_DEPTH_TEST);
}

OpenGLRendererAPI::~OpenGLRendererAPI()
{

}

void OpenGLRendererAPI::setClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::drawIndexed(const OwnRef<VertexArray>& vertexArray, int32_t count = 0)
{
	//TODO: materials textures etc.
	count = count ? count : vertexArray->getIndexBuffer()->getCount();
	vertexArray->bind();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	vertexArray->unbind();
}