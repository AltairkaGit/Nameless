#pragma once
#include "Core/texture.h"
#include <glad/glad.h>

class OpenGLTexture2D : public Texture2D
{
public:
	OpenGLTexture2D(const OwnRef<Image>& image, const OwnRef<TextureSampler>& sampler);
	virtual ~OpenGLTexture2D();

	virtual void bind(uint32_t slot = 0) const override;
	virtual void setData(void* data, uint32_t size) override;

	virtual uint32_t getWidth() const override { return m_Width; }
	virtual uint32_t getHeight() const override { return m_Height; }
	virtual uint32_t getSamplerId() const override { return m_SamplerId; }
	virtual uint32_t getRendererId() const override { return m_RendererId; }
	virtual const std::string& getName() const override{ return m_Name; }
private:
	std::string m_Name = "";
	uint32_t m_RendererId, m_SamplerId;
	uint32_t m_Width, m_Height;
	GLenum m_InternalFormat, m_DataFormat;
};