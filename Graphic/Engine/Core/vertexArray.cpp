#include "vertexArray.h"
#include "renderer.h"
#include "OpenGL/OpenGLVertexArray.h"

OwnRef<VertexArray> VertexArray::create()
{
	switch (Renderer::getAPI())
	{
	case RendererAPI::API::None: return nullptr;
	case RendererAPI::API::OpenGL: return createOwnRef<OpenGLVertexArray>();
	}
}
