#include "buffer.h"
#include "renderer.h"
#include "OpenGL/OpenGLBuffer.h"

OwnRef<VertexBuffer> VertexBuffer::create(uint32_t size)
{
	switch (Renderer::getAPI())
	{
	case RendererAPI::API::None: return nullptr;
	case RendererAPI::API::OpenGL: return createOwnRef<OpenGLVertexBuffer>(size);
	}
	return nullptr;
}

OwnRef<VertexBuffer> VertexBuffer::create(Vertex* vertices, uint32_t size)
{
	switch (Renderer::getAPI())
	{
	case RendererAPI::API::None: return nullptr;
	case RendererAPI::API::OpenGL: return createOwnRef<OpenGLVertexBuffer>(vertices, size);
	}
	return nullptr;
}

OwnRef<VertexBuffer> VertexBuffer::create(const std::vector<Vertex>& vertices)
{
	switch (Renderer::getAPI())
	{
	case RendererAPI::API::None: return nullptr;
	case RendererAPI::API::OpenGL: return createOwnRef<OpenGLVertexBuffer>(vertices, vertices.size());
	}
	return nullptr;
}

//================

OwnRef<IndexBuffer> IndexBuffer::create(uint32_t* indices, uint32_t count)
{
	switch (Renderer::getAPI())
	{
	case RendererAPI::API::None: return nullptr;
	case RendererAPI::API::OpenGL: return createOwnRef<OpenGLIndexBuffer>(indices, count);
	}
	return nullptr;
}

OwnRef<IndexBuffer> IndexBuffer::create(const std::vector<uint32_t>& indices, uint32_t count)
{
	switch (Renderer::getAPI())
	{
	case RendererAPI::API::None: return nullptr;
	case RendererAPI::API::OpenGL: return createOwnRef<OpenGLIndexBuffer>(indices, count);
	}
	return nullptr;
}