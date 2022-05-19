#pragma once
#include <string>
#include "base.h"
#include "image.h"
#include "sampler.h"

class Texture
{
public:
	virtual ~Texture() = default;

	virtual void bind(uint32_t slot = 0) const = 0;
	virtual void setData(void* data, uint32_t size) = 0;

	virtual uint32_t getRendererId() const = 0;
	virtual uint32_t getSamplerId() const = 0;
	
	virtual const std::string& getName() const = 0;
};

class Texture2D : public Texture
{
public:
	virtual uint32_t getWidth() const = 0;
	virtual uint32_t getHeight() const = 0;

	static OwnRef<Texture2D> create(const OwnRef<Image>& image, const OwnRef<TextureSampler>& sampler);	
};