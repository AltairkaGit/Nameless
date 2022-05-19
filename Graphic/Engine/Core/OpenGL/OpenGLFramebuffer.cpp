#include "OpenGLFramebuffer.h"
#include <glad/glad.h>

static const uint32_t s_MaxFramebufferSize = 8192;

namespace FramebufferUtils
{

	static GLenum textureTarget(bool multisampled)
	{
		return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
	}

	static void createTextures(bool multisampled, uint32_t* outId, uint32_t count)
	{
		glCreateTextures(textureTarget(multisampled), count, outId);
	}

	static void bindTexture(bool multisampled, uint32_t rendererId)
	{
		glBindTexture(textureTarget(multisampled), rendererId);
	}

	static void attachColorTexture(uint32_t rendererId, uint32_t samples, GLenum internalFormat, GLenum format, uint32_t width, uint32_t height, int32_t index)
	{
		bool multisampled = samples > 1;
		if (multisampled)
		{
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, 0);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, textureTarget(multisampled), rendererId, 0);
	}

	static void attachDepthTexture(uint32_t rendererId, uint32_t samples, GLenum internalFormat, GLenum attachmentType, uint32_t width, uint32_t height)
	{
		bool multisampled = samples > 1;
		if (multisampled)
		{
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, 0);
		}
		else
		{
			glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat, width, height);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, textureTarget(multisampled), rendererId, 0);
	}

	static bool isDepthFormat(FramebufferTexFormat format)
	{
		switch (format)
		{
		case FramebufferTexFormat::DEPTH24STENCIL8: return 1;
		}
		return 0;
	}

	static GLenum getOpenGLTextureFormat(FramebufferTexFormat format)
	{
		switch (format)
		{
		case FramebufferTexFormat::RGBA8: return GL_RGBA8;
		case FramebufferTexFormat::RED_INT: return GL_RED_INTEGER;
		}
		return 0;
	}
}

OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpec& specification)
	: m_Spec(specification)
{
	for (auto spec : m_Spec.m_Attachments.m_Attachments)
	{
		if (!FramebufferUtils::isDepthFormat(spec.m_TextureFormat))	m_ColorAttachmentSpec.emplace_back(spec);
		else m_DepthAttachmentSpec = spec;
	}

	invalidate();
}

OpenGLFramebuffer::~OpenGLFramebuffer()
{
	glDeleteFramebuffers(1, &m_RendererID);
	glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
	glDeleteTextures(1, &m_DepthAttachment);
}

void OpenGLFramebuffer::invalidate()
{
	if (m_RendererID)
	{
		glDeleteBuffers(1, &m_RendererID);
		glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
		glDeleteTextures(1, &m_DepthAttachment);

		m_ColorAttachments.clear();
		m_DepthAttachment = 0;
	}

	glCreateFramebuffers(1, &m_RendererID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

	bool multisampled = m_Spec.m_Samples > 1;

	//attachments
	if (m_ColorAttachmentSpec.size())
	{
		m_ColorAttachments.resize(m_ColorAttachmentSpec.size());
		FramebufferUtils::createTextures(multisampled, m_ColorAttachments.data(), m_ColorAttachments.size());

		for (uint32_t i = 0; i < m_ColorAttachments.size(); i++)
		{
			FramebufferUtils::bindTexture(multisampled, m_ColorAttachments[i]);
			switch (m_ColorAttachmentSpec[i].m_TextureFormat)
			{
			case FramebufferTexFormat::RGBA8: 
				FramebufferUtils::attachColorTexture(m_ColorAttachments[i], m_Spec.m_Samples, GL_RGBA8, GL_RGBA, m_Spec.m_Width, m_Spec.m_Height, i);
				break;
			case FramebufferTexFormat::RED_INT:
				FramebufferUtils::attachColorTexture(m_ColorAttachments[i], m_Spec.m_Samples, GL_R32I, GL_RED_INTEGER, m_Spec.m_Width, m_Spec.m_Height, i);
				break;
			}
		}
	}
	
	if (m_DepthAttachmentSpec.m_TextureFormat != FramebufferTexFormat::None)
	{
		FramebufferUtils::createTextures(multisampled, &m_DepthAttachment, 1);
		FramebufferUtils::bindTexture(multisampled, m_DepthAttachment);
		switch (m_DepthAttachmentSpec.m_TextureFormat)
		{
		case FramebufferTexFormat::DEPTH24STENCIL8:
			FramebufferUtils::attachDepthTexture(m_DepthAttachment, m_Spec.m_Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Spec.m_Width, m_Spec.m_Height);
			break;
		}
	}

	if (m_ColorAttachments.size() > 1)
	{
		GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
		glDrawBuffers(m_ColorAttachments.size(), buffers);
	}
	else if (m_ColorAttachments.empty())
	{
		//depth only
		glDrawBuffer(GL_NONE);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFramebuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	glViewport(0, 0, m_Spec.m_Width, m_Spec.m_Height);
}

void OpenGLFramebuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFramebuffer::resize(uint32_t width, uint32_t height)
{
	if (width == 0 || height == 0 || width > s_MaxFramebufferSize || height > s_MaxFramebufferSize) return;
	m_Spec.m_Width = width;
	m_Spec.m_Height = height;
	invalidate();
}

int32_t OpenGLFramebuffer::readPixel(uint32_t attachmentIndex, uint32_t x, uint32_t y)
{
	if (attachmentIndex >= m_ColorAttachments.size())
	{
		std::cout << "attachment index bigger than size of m_ColorAttachments" << '\n';
		return -1;
	}

	glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
	int pixelData;
	glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
	return pixelData;
}

void OpenGLFramebuffer::clearAttachment(uint32_t attachmentIndex, uint32_t val)
{
	if (attachmentIndex >= m_ColorAttachments.size())
	{
		std::cout << "attachment index bigger than size of m_ColorAttachments" << '\n';
		return;
	}

	auto& spec = m_ColorAttachmentSpec[attachmentIndex];
	glClearTexImage(m_ColorAttachments[attachmentIndex], 0, FramebufferUtils::getOpenGLTextureFormat(spec.m_TextureFormat), GL_INT, &val);
}