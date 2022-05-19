#include "context.h"
#include "renderer.h"
#include "OpenGL/OpenGLContext.h"

Scope<Context> Context::Create(void* window)
{
	
	switch (Renderer::getAPI())
	{
	case RendererAPI::API::None: return nullptr;
	case RendererAPI::API::OpenGL: return createScope<OpenGLContext>(static_cast<Window*>(window));
	}
	return nullptr;
}