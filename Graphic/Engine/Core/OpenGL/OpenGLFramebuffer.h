#pragma once
#include "Core/framebuffer.h"

class OpenGLFramebuffer : public Framebuffer
{
public:
	OpenGLFramebuffer(const FramebufferSpec& spec);
	~OpenGLFramebuffer();
	void invalidate();

	virtual void bind() override;
	virtual void unbind() override;

	virtual void resize(uint32_t width, uint32_t height) override;
	virtual int32_t readPixel(uint32_t atachmentIndex, uint32_t x, uint32_t y) override;
	virtual void clearAttachment(uint32_t attachmentIndex, uint32_t val) override;
	virtual uint32_t getColorAttachmentRendererId(uint32_t index = 0) override { return m_ColorAttachments[index]; }
	virtual const FramebufferSpec& getSpec() const override { return m_Spec; }

private:
	uint32_t m_RendererID = 0;

	FramebufferSpec m_Spec;
	std::vector<FramebufferTexSpec> m_ColorAttachmentSpec;
	FramebufferTexSpec m_DepthAttachmentSpec = FramebufferTexFormat::None;

	std::vector<uint32_t> m_ColorAttachments;
	uint32_t m_DepthAttachment = 0;
};