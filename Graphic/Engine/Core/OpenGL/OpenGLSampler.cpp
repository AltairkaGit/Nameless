#include "OpenGLSampler.h"
#include <glad/glad.h>

namespace SamplerUtils
{
	uint32_t getFiltering(Filtering filtering)
	{
		switch (filtering)
		{
		case Filtering::Nearest: return GL_NEAREST;
		case Filtering::Billinear: return GL_LINEAR;
		}
	}

	uint32_t getWrapping(Wrapping wrapping)
	{
		switch (wrapping)
		{
		case Wrapping::Repeat: return GL_REPEAT;
		case Wrapping::Clamp: return GL_CLAMP_TO_EDGE;
		}
	}

	float_t getAnisotropyExt(SamplerAnisotropy anisotropyExt)
	{
		switch (anisotropyExt)
		{
		case SamplerAnisotropy::X1:  return  1.0f;
		case SamplerAnisotropy::X2:  return  2.0f;
		case SamplerAnisotropy::X4:  return  4.0f;
		case SamplerAnisotropy::X8:  return  8.0f;
		case SamplerAnisotropy::X16: return 16.0f;
		}
	}
}

OpenGLSampler::OpenGLSampler(SamplerAnisotropy anisotropyExt, Filtering filtering, Wrapping wrapping)
	:	m_AnisotropyExt(SamplerUtils::getAnisotropyExt(anisotropyExt)),
		m_Filtering(SamplerUtils::getFiltering(filtering)),
		m_Wrapping(SamplerUtils::getWrapping(wrapping))		
{
	glCreateSamplers(1, &m_RendererId);
	glSamplerParameteri(m_RendererId, GL_TEXTURE_WRAP_S, m_Wrapping);
	glSamplerParameteri(m_RendererId, GL_TEXTURE_WRAP_T, m_Wrapping);
	glSamplerParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, m_Filtering);
	glSamplerParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, m_Filtering);
	glSamplerParameterf(m_RendererId, GL_TEXTURE_MAX_ANISOTROPY_EXT, m_AnisotropyExt);
}

OpenGLSampler::~OpenGLSampler()
{
	glDeleteSamplers(1, &m_RendererId);
}

void OpenGLSampler::bind(uint32_t slot) const
{
	glBindSampler(slot, m_RendererId);
}

