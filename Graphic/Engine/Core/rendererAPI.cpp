#include "rendererAPI.h"
#include "OpenGL/OpenGLRendererAPI.h"

RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

Scope<RendererAPI> RendererAPI::create()
{
	switch (RendererAPI::s_API)
	{
	case API::None: return nullptr;
	case API::OpenGL: return createScope<OpenGLRendererAPI>();
	}
	return nullptr;
}

