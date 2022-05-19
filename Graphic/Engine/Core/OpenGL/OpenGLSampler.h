#pragma once
#include "Core/sampler.h"

class OpenGLSampler : TextureSampler
{
public:
	OpenGLSampler(SamplerAnisotropy anisotropyExt, Filtering filtering, Wrapping wrapping);
	virtual ~OpenGLSampler();

	virtual void bind(uint32_t slot) const override;

	virtual uint32_t getMagFilter() const override { return m_Filtering; }
	virtual uint32_t getMinFilter() const override { return m_Filtering; }

	virtual uint32_t getWrapS() const override { return m_Wrapping; }
	virtual uint32_t getWrapT() const override { return m_Wrapping; }

	virtual float_t getMaxAnisotropyExt() const override { return m_AnisotropyExt; }
private:
	uint32_t m_RendererId;

	uint32_t m_Filtering;
	uint32_t m_Wrapping;
	float_t m_AnisotropyExt;
};
