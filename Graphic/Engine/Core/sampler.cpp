#include "sampler.h"
#include "renderer.h"
#include "OpenGL/OpenGLSampler.h"

OwnRef<TextureSampler> TextureSampler::create(Filtering filtering = Filtering::Billinear,
Wrapping wrapping = Wrapping::Repeat, SamplerAnisotropy anisotropyExt = SamplerAnisotropy::X16)
{
	switch (Renderer::getAPI())
	{
	case RendererAPI::API::None: return 0;
	case RendererAPI::API::OpenGL: return createOwnRef<TextureSampler>(anisotropyExt, filtering, wrapping);
	}
}
