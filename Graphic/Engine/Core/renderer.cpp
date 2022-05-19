#include "renderer.h"

void Renderer::init(const uint32_t& ScreenWidth, const uint32_t& ScreenHeight, const std::string& name)
{
	s_RendererAPI = RendererAPI::create();
	s_Window = Window::create(WindowProps(name, ScreenWidth, ScreenHeight));
}

void Renderer::shutdown()
{
	
}

void Renderer::submit(const OwnRef<Shader>& shader, const OwnRef<VertexArray>& vertexArray, int32_t count = 0)
{
	shader->bind();
	s_RendererAPI->drawIndexed(vertexArray, count);
	shader->unbind();
}

void Renderer::clear()
{
	s_RendererAPI->clear();
}