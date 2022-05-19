#include "unifornBuffer.h"
#include "renderer.h"
#include "OpenGL/OpenGLUniformBuffer.h"

OwnRef<UniformBuffer> UniformBuffer::create(uint32_t size, uint32_t binding)
{
	switch (Renderer::getAPI())
	{
	case RendererAPI::API::None: return nullptr;
	case RendererAPI::API::OpenGL: return createOwnRef<OpenGLUniformBuffer>(size, binding);
	}
}
