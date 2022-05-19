#pragma once
#include "Core/base.h"
#include "Libs/stb_image.h"

namespace gltf
{
	enum class ImageType
	{
		None = 0, Jpeg, Png,
	};
	
	struct ImageProps
	{
	
		std::string uri = "";
		ImageType type = ImageType::None;
		uint32_t bufferView = INT32_MAX;
	};

	/** Storing raw data from disk on RAM
		creating by uri	(load from disk or encoding base64 uri)
		or loading from buffer
	*/
	struct Image
	{
		Image(const std::string& uri, ImageType type);
		Image();

		~Image();
		Image(Image&);
		Image& operator=(Image&);

		BYTE* data;
		ImageProps props;
	};


	class ImageManager
	{

	};
}