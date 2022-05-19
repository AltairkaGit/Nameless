#include "OpenGLTexture.h"

OpenGLTexture2D::OpenGLTexture2D(const OwnRef<Image>& image, const OwnRef<TextureSampler>& sampler)
	: m_Name(name)
{
	int width, height, channels;
	
	stbi_uc* data = nullptr;
	data = stbi_load(path.c_str(), &width, &height, &channels, 0);


	if (data)
	{
		
		m_Width = width;
		m_Height = height;

		GLenum dataFormat = 0, internalFormat = 0;
		switch (channels)
		{
		case 1:
			dataFormat = GL_RED;
			internalFormat = GL_R8;
			break;
		case 3:
			dataFormat = GL_RGB;
			internalFormat = GL_RGB8;
			break;
		case 4:
			dataFormat = GL_RGBA;
			internalFormat = GL_RGBA8;
		}

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;
		m_Type = type;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
		
		glBindSampler(m_RendererId, m_SamplerId);
		glTextureStorage2D(m_RendererId, 1, m_InternalFormat, m_Width, m_Height);

		//Binding sampler

		glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
		
		stbi_image_free(data);
	}
	else
	{
		std::cout << "Fail: load texture, path: " << path << '\n';
	}
	
}

OpenGLTexture2D::~OpenGLTexture2D()
{
	glDeleteTextures(1, &m_RendererId);

}

void OpenGLTexture2D::setData(void* data, uint32_t size)
{
	glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
}

void OpenGLTexture2D::bind(uint32_t slot) const
{
	glBindTextureUnit(slot, m_RendererId);
}