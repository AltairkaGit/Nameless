#include "framebuffer.h"
#include "renderer.h"
#include "OpenGL/OpenGLFramebuffer.h"

OwnRef<Framebuffer> Framebuffer::create(const FramebufferSpec& spec)
{
	switch (Renderer::getAPI())
	{
	case RendererAPI::API::None: return nullptr;
	case RendererAPI::API::OpenGL: return createOwnRef<OpenGLFramebuffer>(spec);
	}
}