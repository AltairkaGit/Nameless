#include "image.h"

Image::Image(uint32_t width, uint32_t height, uint32_t channels)
	: m_Width(width), m_Height(height), m_Channels(channels)
{
}

Image::Image(const std::string& path)
	: m_Uri(path)
{
	stbi_set_flip_vertically_on_load(1);
	int width, height, channels;
	m_Data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	if (m_Data == 0) std::cout << "Failed image loading, path: " << path << '\n';
	else
	{
		m_Width = width;
		m_Height = height;
		m_Channels = channels;
	}
}

Image::~Image()
{
	freeData();
}

void Image::freeData()
{
	stbi_image_free(m_Data);
	m_Data = 0;
}