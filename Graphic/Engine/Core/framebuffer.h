#pragma once
#include "base.h"
#include <vector>

enum class FramebufferTexFormat
{
	None = 0,
	RGBA8,
	RED_INT,
	DEPTH24STENCIL8,
	Depth = DEPTH24STENCIL8
};

struct FramebufferTexSpec
{
	FramebufferTexSpec() = default;
	FramebufferTexSpec(FramebufferTexFormat format)
		: m_TextureFormat(format)
	{}
	FramebufferTexFormat m_TextureFormat = FramebufferTexFormat::None;
};

struct FramebufferAttachmentSpec
{
	FramebufferAttachmentSpec() = default;
	FramebufferAttachmentSpec(const std::initializer_list<FramebufferTexSpec>& attachments)
		: m_Attachments(attachments)
	{}

	std::vector<FramebufferTexSpec> m_Attachments;
};

struct FramebufferSpec
{
	uint32_t m_Width, m_Height;
	uint32_t m_Samples = 1;
	FramebufferAttachmentSpec m_Attachments;
	bool m_SwapChainTarget = 0;
};


class Framebuffer
{
public:
	virtual ~Framebuffer() = default;

	virtual void bind() = 0;
	virtual void unbind() = 0;

	virtual void resize(uint32_t width, uint32_t height) = 0;
	virtual int32_t readPixel(uint32_t atachmentIndex, uint32_t x, uint32_t y) = 0;
	virtual void clearAttachment(uint32_t atachmentIndex, uint32_t val) = 0;
	virtual uint32_t getColorAttachmentRendererId(uint32_t index = 0) = 0;
	virtual const FramebufferSpec& getSpec() const = 0;

	static OwnRef<Framebuffer> create(const FramebufferSpec& spec);
};
