#include "texture.h"
#include "renderer.h"
#include "OpenGL/OpenGLTexture.h"

OwnRef<Texture2D> Texture2D::create(const OwnRef<Image>& image, const OwnRef<TextureSampler>& sampler)
{
	switch (Renderer::getAPI())
	{
	case RendererAPI::API::None: return nullptr;
	case RendererAPI::API::OpenGL: return createOwnRef<OpenGLTexture2D>(image, sampler);
	}
}