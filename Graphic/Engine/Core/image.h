#pragma once
#include <string>
#include "base.h"
#include "Libs/stb_image.h"

class Image
{
public:
	Image(const std::string& path);
	Image(uint32_t width, uint32_t height, uint32_t channels);

	void freeData();

	const Byte* getData() const { return m_Data; }
	const uint32_t getSize() const { return m_Size; }
	const uint32_t getWidth() const { return m_Width; }
	const uint32_t getHeight() const { return m_Height; }
	const uint32_t getChannels() const { return m_Channels; }
	const std::string& getUri() const { return m_Uri; }

	~Image();
	Image(Image&) = delete;
	Image& operator=(Image&) = delete;
private:
	Byte* m_Data = 0;

	uint32_t m_Width = 0;
	uint32_t m_Height = 0;
	uint32_t m_Channels = 0;
	/** Depth - number of surfaces
		for cubemaps = 6,
		otherwise = 1
	*/
	uint32_t m_Size = 0;

	std::string m_Uri = "";
};
